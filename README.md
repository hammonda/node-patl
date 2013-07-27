#### Node module to expose the filter strings with Levenshtein automata algorithms <br>from the C++ PATL (Practical Algorithm Template Library) library
See [PATL](https://code.google.com/p/patl/) for full details of the underlying C++ library.

##### How to build
```
dh1509@690:~/node-patl$ node-gyp rebuild
```
Build tested with
```
node --version 
  v0.10.12
node-gyp --version 
  v0.10.5
gcc --version gcc 
  (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2
lsb_release -a
  No LSB modules are available.
  Distributor ID:  Ubuntu
  Description:	Ubuntu 12.10
  Release:	12.10
  Codename:	quantal
```

##### Example Usage
```javascript
var addon = require('./build/Release/nodepatl');

var patl = new addon.Patl;

patl.loadDictionary(['WORD.LST'], function (err, size) {
  if (!err) {
    patl.searchDictionary('undfined', 2, function (results) {
      console.log(results);
    });
  } else {
    console.error(err);
  }
});
```
##### Output
```
dh1509@690:~/node-patl$ node example.js 
Loading dictionary file WORD.LST  dictionary size 173528
[ [],
  [ 'undefined' ],
  [ 'uncoined',
    'undefiled',
    'undenied',
    'undine',
    'undines',
    'undrained',
    'undried',
    'unfired',
    'unfixed',
    'unified',
    'unjoined',
    'unlined',
    'unmined',
    'unrefined',
    'untwined',
    'unveined' ] ]
```
#### Other Examples
* [A simple JSON server](server.js)
* [Memory/Performance Test](mem_test.js)
