var functions = {};

functions["asig"] = function(ele){
    var child = ele.children[0];
    var variable = child.children[0].value;
    var value = child.children[2].value;

    return {
        "type":"asig",
        "var": variable,
        "value":value
    };

};

functions["expr-op"] = function(ele){
    var child = ele.children[0];
    var variable = child.children[0].value;
    var op1 = child.children[2].value;
    var select = child.children[3];
    var operation = select.options[select.selectedIndex].value;
    var op2 = child.children[4].value;

    return {
        "type": "expr-op",
        "var": variable,
        "op1": op1,
        "operation": operation,
        "op2": op2
    };

}

functions["expr-log"] = function(ele){
        var child = ele.children[0];
        var op1 = child.children[0].value;
        var select = child.children[1];
        var operation = select.options[select.selectedIndex].value;
        var op2 = child.children[2].value;

        return {
            "type":"expr-log",
            "op1": op1,
            "operation": operation,
            "op2": op2
        };
}

functions["loop"] = function(ele){
    var times = ele.children[0].children[0].children[0].value;
    var inside = ele.children[1];
    var childs = parse(inside.children);

    return{
        "type":"loop",
        "times": times,
        "children": childs
    };

}

functions["while"] = function(ele){
  var log_e = ele.children[0]
                 .children[0]
                 .children[1];
  var log = parse(log_e.children)[0];
  var ctx = parse(ele.children[1].children);
  return {
    "type": "while",
    "conditional": log,
    "children": ctx
  }


}

functions["if"] = function(ele){

  var childs = ele.children[0].children[1].children;
  var logica = parse(childs)[0];
  var content = ele.children[1];
  var conten_c = parse(content.children);

  return {
    "type": "if",
    "conditional": logica,
    "children": conten_c
  };
}

functions["ifelse"] = function(ele){
  var childs = ele.children[0].children[1].children;
  var logica1 = parse(childs)[0];
  var content1 = ele.children[1];
  var conten_c1 = parse(content1.children);
  var content_c2 = parse(ele.children[3].children);

  return {
    "type": "ifelse",
    "conditional1": logica1,
    "children1": conten_c1,
    "children2": content_c2
  };


}

functions["mess"] = function(ele){
  var mess = ele.children[0].children[1].value;
  return {
    "type": "mess",
    "message": mess

  };
}

functions["delay"] = function(ele){
  var mess = ele.children[0].children[1].value;
  return {
    "type": "delay",
    "delay": mess

  };
}

functions["led"] = function(ele){
    var led = ele.children[0].children[0];
    var led_v = led.options[led.selectedIndex].value;
    var vari = ele.children[0].children[2].value;
        
    return {
      "type": "led",
      "led": led_v,
      "op": vari  
    };    
}

functions["lede"] = function(ele){
    var led1 = ele.children[0].children[0];
    var led_v1 = led1.options[led1.selectedIndex].value;
    
    var led2 = ele.children[0].children[2];
    var led_v2 = led2.options[led2.selectedIndex].value;
    
    return {
      "type": "led",
      "led": led_v1,
      "op": led_v2  
    };    
}

functions["motor"] = function(ele){
    var led1 = ele.children[0].children[0];
    var led_v1 = led1.options[led1.selectedIndex].value;
    
    var led2 = ele.children[0].children[2];
    var led_v2 = led2.options[led2.selectedIndex].value;
    
    return {
      "type": "motor",
      "motor": led_v1,
      "op": led_v2  
    }; 
    
}

functions["boton"] = function(ele){
    var led = ele.children[0].children[2];
    var led_v = led.options[led.selectedIndex].value;
    var vari = ele.children[0].children[0].value;
        
    return {
      "type": "boton",
      "boton": led_v,
      "op": vari  
    };    
}

functions["temp"] = function(ele){

    var vari = ele.children[0].children[0].value;
        
    return {
      "type": "temp",
      "op": vari  
    };    
}

functions["analog"] = function(ele){
    var vari = ele.children[0].children[0].value;
        
    return {
      "type": "analog",
      "op": vari  
    };    
}

functions["begin"] = function(ele){
    return {"type":"begin"};
}

functions["end"] = function(ele){
    return {"type":"end"};
}





function parse(elements){

    var result = [];

    for(var i = 0; i < elements.length; ++i){
        var element = elements[i];
        if(element.tagName != "DIV"){
            continue;
        }
        var type = element.getAttribute("tipo");
        var obj = functions[type](element);
        result.push(obj);
    }

    return result;

}
