/*
  Copyright (c) 2012 The Chromium Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.
*/

// Automation utilities for running the V8 Benchmark as a UI test.

function Automation() {
  this.score = '';
  this.results = {};
}

Automation.prototype.SetDone = function() {
  console.log("score: " + this.GetScore());
  for (var result in this.results) {
    if (this.results.hasOwnProperty(result))
      console.log(result + ": " + this.results[result]);
  }
  document.cookie = '__done=1; path=/';
};

Automation.prototype.SetScore = function (score) {
  this.score = score;
};

Automation.prototype.GetScore = function() {
  return this.score;
};

Automation.prototype.AddResult = function(name, result) {
  this.results[name] = result;
};

Automation.prototype.GetResults = function() {
  return this.results;
};

automation = new Automation();
