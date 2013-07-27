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
