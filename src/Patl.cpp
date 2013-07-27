#include <Patl.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <utility>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

Patl::Patl () { }

Patl::~Patl () { }

/*!@brief Static factory function to create the Patl class. Called from V8.
 * @oaram[in] args  The supplied V8 arguments.
 * @return A handle to the wrapped C++ class.
 */
v8::Handle<v8::Value> Patl::New(const v8::Arguments& args) {
  v8::HandleScope scope;
  Patl *obj = new Patl();
  obj->Wrap(args.This());
  return args.This();
}

/*!@brief Load a list of dictionary files, each containing a list of words.
 * @param[in] in  The input arguments: list of file names.
 * @param[out] out  The output arguments: error message, total number of words.
 */
void Patl::loadDictionary (const Args<vector_string_t>& in,
    Args<string_t, uint32_t>& out) {
  dictionary.clear();
  partial_match_set_itr_t hint(dictionary.end());
  string_t str;
  for (vector_string_t::const_iterator itr = in.arg0.begin();
      itr != in.arg0.end(); itr++) {
    printf("Loading dictionary file %s", (*itr).c_str());
    std::ifstream fin((*itr).c_str());
    if (fin.is_open()) {
      while (fin >> str) {
        hint = dictionary.insert(hint, str);
      }
    } else {
      out.arg0 = "Unable to open input file!";
    }
    fin.close();
    printf("  dictionary size %d\n", dictionary.size());
  }
  out.arg1 = dictionary.size();
}

/*!@brief Search the current dictionary looking for non-exact matched to a
 * string based on maximum specified Levenshtein distance.
 * @param[in] in  The input arguments: match string, max distance.
 * @param[out] out  The output arguments: matrix of string results, rows grouped
 *   by equal Levenshtein distance, starting at zero.
 */
void Patl::searchDictionary (const Args<string_t,uint32_t>& in,
    Args<matrix_string_t>& out) {
  leven_dist_set_t ld(dictionary, in.arg1, in.arg0.c_str());
  leven_dist_set_itr_t beg(dictionary.begin(ld));
  leven_dist_set_itr_t end(dictionary.end(ld));
  leven_dist_set_itr_t it(beg);
  out.arg0.resize(1 + in.arg1);
  for (; it != end; ++it) {
    out.arg0[it.decis().distance()].push_back(*it);
  }
}
