    "use strict"
    
    var bloques = document.getElementById("blocks");
    var programa = document.getElementById("program");
    
    var drake = dragula([bloques, programa], {
      copy: true,
      accepts: function(el, target, source, sibling){
         // console.log("accept: " + target.className);
          if(el.className.indexOf("p-expr-log") !== -1
            && target.className.indexOf("p-logica") === -1){
              return false;
            }
          if (target.className.indexOf("blocks") !== -1
                || !sibling
                || sibling.className.indexOf("p-inicio") !== -1 ){
              return false;              
          }
          return true;

      },
      moves: dontMove
  });  
  drake.on("drop", function(el, target ,source){
      //console.log(target.innerHTML);
      if(target &&
         target.className.indexOf("p-logica") !== -1){
        removeTag("<br>", target);
       //rmClass(el, "gu-transit");
      }
      
      
      if(el.className.indexOf("p-repetir") !== -1){
          var mid = getChildByClassName(el, "p-repetir-mid");
          drake.containers.push(mid);          
      }
        else if(el.className.indexOf("p-sino") !== -1){
          var mid1 = getChildByClassName(el, "p-sino-mid-1");
          var mid2 = getChildByClassName(el, "p-sino-mid-2");
          drake.containers.push(mid1);
          drake.containers.push(mid2);          
      }
      else if(el.className.indexOf("p-si") !== -1){
          var mid = getChildByClassName(el, "p-si-mid");
          var sup = getChildByClassName(el, "p-si-sup");
          var log = getChildByClassName(sup, "p-logica");
          drake.containers.push(log);
          drake.containers.push(mid);          

      }    
      
  });
    

dragula([programa], {
     removeOnSpill: true,
     moves: dontMove
   
});

function dontMove(el, container, handle)
{
         //console.log("moves:" + el.className);
         if( el.className.indexOf("p-inicio") !== -1
             || el.className.indexOf("label") !== -1 
             || el.className.indexOf("p-fin") !== -1){
             return false;
         }
         return true;         
}

function getChildByClassName(el, className){
    var childs = el.childNodes;
    for(var i = 0; i < childs.length; ++i){
        if(childs[i].className &&
            childs[i].className.indexOf(className) !== -1){
            return childs[i];
        }        
    }
}

function removeTag(tag, el){
  var html = el.innerHTML.replace(new RegExp(tag, 'g' ), "");
  el.innerHTML = html;
  //console.log(html);
  
}

function rmClass (el,  className) {
  el.className = el.className.replace(className, ' ');
  //console.log(el.className);
}