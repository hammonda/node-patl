var addon = require('./build/Release/nodepatl');
var fs = require('fs');
var EventEmitter = require('events').EventEmitter;
var util = require('util');

var patl = new addon.Patl;
var ee = new EventEmitter;

var sims = 100000;
var count = 1;
var time;

ee.on('work', work);
ee.on('next', next);
ee.on('end', function () {
  var diff = process.hrtime(time);
  var secs = diff[0] + diff[1]/1000000000;
  console.log('benchmark took %d seconds', secs);
  console.log(' %d per second', sims/secs);  
});

function callback (results) {
  if (count > sims) {
    console.log(results);
  }
  ee.emit('next');
}

function work () {
  patl.searchDictionary('test', 1, callback);
}

function next () {
  if (count <= sims) {
    if (count % 5000 === 0) {
      console.log(util.inspect(process.memoryUsage()));
    }
    count++;
    ee.emit('work');
  } else {
    ee.emit('end');
  }
}

patl.loadDictionary([/*'scowl/english-words.10',*/'WORD.LST'], 
		function (err, size) {
  time = process.hrtime();
  console.log('dictionary size', size);
  ee.emit('next');
});
