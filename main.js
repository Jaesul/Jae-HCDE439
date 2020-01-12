"use strict";
(function() {

  window.addEventListener("load", init);

  function init() { 
    let header = qs()
    let observer = scrlCntObs();
    let transitionItms = qsa('.no-opacity');
    transitionItms.forEach(element => {
        observer.observe(element);
    });
  }

  function scrlCntObs() {
    let options = {
      rootMargin: '0px 0px 0px 0px',
      threshold: 0.4
    }

    let observer = new IntersectionObserver(
      (entries) => {
        entries.forEach(entry => {
          if(entry.isIntersecting) {
            entry.target.classList.remove('no-opacity', 'right-20');
          }
        });
      }, options
    )
    return observer;
  }

  function qsa(elementName) {
    return document.querySelectorAll(elementName);
  }

  function qs(elementName) {
    return document.querySelector(elementName);
  }

  function id(idName) {
    return document.getElementById(idName);
  }
})();