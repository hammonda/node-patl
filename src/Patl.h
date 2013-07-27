#ifndef PATL_H
#define PATL_H

#include <string>
#include <stdint.h>
#include <vector>
#include <map>

#include <v8.h>
#include <node.h>

#include <nasync/Args.hpp>
#include <nasync/Method.hpp>

#include <uxn/patl/trie_set.hpp>
#include <uxn/patl/trie_map.hpp>
#include <uxn/patl/levenshtein.hpp>

using namespace nasync;

namespace patl = uxn::patl;

class Patl : public node::ObjectWrap {
public:
  typedef std::string string_t;
  typedef uint32_t word_index_t;

  typedef std::map<string_t, word_index_t> exact_match_map_t;
  typedef patl::trie_map<string_t, word_index_t> partial_match_map_t;
  typedef patl::trie_set<string_t> partial_match_set_t;
  typedef partial_match_set_t::iterator partial_match_set_itr_t;
  typedef partial_match_map_t::iterator partial_match_map_itr_t;

  typedef std::vector<string_t> vector_string_t;
  typedef std::vector<word_index_t> vector_word_index_t;

  typedef std::vector<vector_string_t> matrix_string_t;

  typedef patl::levenshtein_tp_distance<partial_match_set_t, true> leven_dist_set_t;
  typedef patl::levenshtein_tp_distance<partial_match_map_t, true> leven_dist_map_t;

  typedef partial_match_set_t::const_partimator<leven_dist_set_t> leven_dist_set_itr_t;
  typedef partial_match_map_t::const_partimator<leven_dist_map_t> leven_dist_map_itr_t;

  /*!@brief Static factory function to create the Patl class. Called from V8.
   * @oaram[in] args  The supplied V8 arguments.
   * @return A handle to the wrapped C++ class.
   */
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  /*!@brief Load a list of dictionary files, each containing a list of words.
   * @param[in] in  The input arguments: list of file names.
   * @param[out] out  The output arguments: error message, total number of words.
   */
  void loadDictionary (const Args<vector_string_t>& in, Args<string_t, uint32_t>& out);

  /*!@brief Search the current dictionary looking for non-exact matched to a
   * string based on maximum specified Levenshtein distance.
   * @param[in] in  The input arguments: match string, max distance.
   * @param[out] out  The output arguments: matrix of string results, rows grouped
   *   by equal Levenshtein distance, starting at zero.
   */
  void searchDictionary (const Args<string_t,uint32_t>& in, Args<matrix_string_t>& out);

  typedef void(Patl::*LOAD_DICTIONARY)(const Args<vector_string_t>&, Args<string_t, uint32_t>&);
  typedef void(Patl::*SEARCH_DICTIONARY)(const Args<string_t,uint32_t>&, Args<matrix_string_t>&);

  typedef Method<LOAD_DICTIONARY, &Patl::loadDictionary> LOAD_DICTIONARY_ASYNC;
  typedef Method<SEARCH_DICTIONARY, &Patl::searchDictionary> SEARCH_DICTIONARY_ASYNC;

  virtual ~Patl ();
private:
  Patl ();

  //! A set from strings that can be searched using partial or exact matches.
  partial_match_set_t dictionary;

  //! A map from strings to word indexes that can be searched using exact
  // matches only.
  exact_match_map_t emLookup;

  //! A map from strings to word indexes that can be searched using partial
  // or exact matches.
  partial_match_map_t pmLookup;
};

#endif /* PATL_H */
