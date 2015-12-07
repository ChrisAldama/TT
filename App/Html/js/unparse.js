var f_unparse = {};

f_unparse["ifelse"] = function(obj){
  var ife = document
  .querySelector("[tipo='ifelse']")
  .cloneNode(true);

  var childs = ife.children[1];
  unparse_c(obj.children1, childs);

  var logica = ife
  .children[0]
  .children[1];

  unparse_c([obj.conditional], logica);

  var childs2 = ife.children[3];
  unparse_c(obj.children2, childs2);  

  return ife;
}

f_unparse["if"] = function(obj){
  var ife = document
  .querySelector("[tipo='if']")
  .cloneNode(true);

  var childs = ife.children[1];
  unparse_c(obj.children, childs);

  var logica = ife
  .children[0]
  .children[1];

  unparse_c([obj.conditional], logica);

  return ife;
}

f_unparse["while"] = function(obj){
  var loop = document
  .querySelector("[tipo='while']")
  .cloneNode(true);

  var inside = loop.children[1];
  unparse_c(obj.children, inside);

  var log_e = loop
  .children[0]
  .children[0]
  .children[1];
  unparse_c([obj.conditional], log_e);

  return loop;
}

f_unparse["loop"] = function(obj){
  var loop = document
  .querySelector("[tipo='loop']")
  .cloneNode(true);

  var inside = loop.children[1];
  unparse_c(obj.children, inside);

  loop
  .children[0]
  .children[0]
  .children[0]
  .value = obj.times;

  return loop;
}

f_unparse["expr-log"] = function(obj){
  var expr = document
  .querySelector("[tipo='expr-log']")
  .cloneNode(true);

  expr
  .children[0]
  .children[0]
  .value = obj.op1;

  expr
  .children[0]
  .children[1]
  .value = obj.operation;

  expr
  .children[0]
  .children[2]
  .value = obj.op2;

  return expr;
}


f_unparse["expr-op"] = function(obj){
  var expr = document
  .querySelector("[tipo='expr-op']")
  .cloneNode(true);

  expr
  .children[0]
  .children[0]
  .value = obj.var;

  expr
  .children[0]
  .children[2]
  .value = obj.op1;

  expr
  .children[0]
  .children[3]
  .value = obj.operation;

  expr
  .children[0]
  .children[4]
  .value = obj.op2;

  return expr;
}

f_unparse["asig"] = function(obj){
  var asig = document
  .querySelector("[tipo='asig']")
  .cloneNode(true);

  asig
  .children[0]
  .children[0]
  .value = obj.var;

  asig
  .children[0]
  .children[2]
  .value = obj.value;

  return asig;
}

f_unparse["analog"] = function(obj){
  var analog = document
  .querySelector("[tipo='analog']")
  .cloneNode(true);

  analog
  .children[0]
  .children[0]
  .value = obj.op;

  return analog;
}

f_unparse["temp"] = function(obj){
  var temp = document
  .querySelector("[tipo='temp']")
  .cloneNode(true);

  temp
  .children[0]
  .children[0]
  .value = obj.op;

  return temp;
}

f_unparse["boton"] = function(obj){
  var boton = document
  .querySelector("[tipo='boton']")
  .cloneNode(true);

  boton
  .children[0]
  .children[2]
  .value = obj.boton;

  boton
  .children[0]
  .children[0]
  .value = onj.op;

  return boton;
}

f_unparse["motor"] = function(obj){
  var motor = document
  .querySelector("[tipo='motor']")
  .cloneNode(true);

  motor
  .children[0]
  .children[0]
  .value = obj.motor;

  motor
  .children[0]
  .children[2]
  .value = obj.op;

  return motor;
}

f_unparse["led"] = function(obj){

  var led = {};
  if(obj[stype] == "lede"){
    led = document
    .querySelector("[tipo='lede']")
    .cloneNode(true);


  }
  else {
    led = document
    .querySelector("[tipo='led']")
    .cloneNode(true);
  }

  led
  .children[0]
  .children[2]
  .value = obj.op;

  led
  .children[0]
  .children[0]
  .value = obj.led;

  return led;
}

f_unparse["delay"] = function(obj){
  var delay = document
    .querySelector("[tipo='delay']")
    .cloneNode(true);

    delay
    .children[0]
    .children[1]
    .value = obj.delay;

    return delay;
}

f_unparse["mess"] = function(obj){
  var mess = document
    .querySelector("[tipo='mess']")
    .cloneNode(true);

  mess
    .children[0]
    .children[1]
    .value = obj.message;

    return mess;
}

f_unparse["begin"] = function(obj){
  var end = '<a class="l-inicio">Inicio</a>';
  var div = document.createElement('div');
  div.className = "p-bloque p-inicio";
  div.setAttribute("tipo", "end");
  div.innerHTML = end;

  return div;
};

f_unparse["end"] = function(obj){
  var end = '<a class="l-inicio">Fin</a>';
  var div = document.createElement('div');
  div.className = "p-bloque p-fin";
  div.setAttribute("tipo", "end");
  div.innerHTML = end;

  return div;
};

function unparse(json){
  var program = JSON.parse(json);
  var p = document.getElementById("program");
  p.innerHTML = "";
  unparse_c(program, p);
}

function unparse_c(list, container){
  for(var i = 0; i < list.length; ++i){
    var type = list[i].type;
    var ele = f_unparse[type](list[i]);
    container.appendChild(ele);
  }
}
