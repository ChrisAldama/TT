var WebChannel = {
  qt: 0,
  ready: function(){
    return WebChannel.qt != 0;
  },
  sendProgram: function(json, callback){
    if(!WebChannel.ready()){
      return false;
    }

    WebChannel
    .qt
    .objects
    .parser
    .load(json, true, callback);
    return true;

  },

  stopProgram: function(){
    if(!WebChannel.ready()){
      return false;
    }

    WebChannel
    .qt
    .objects
    .parser
    .stop();
    return true;
  }
};


(function init_socket(){
  var baseUrl = (/[?&]webChannelBaseUrl=([A-Za-z0-9\-:/\.]+)/
                .exec(location.search)[1]);
  console.log("Connecting to " + baseUrl);
  var socket = new WebSocket(baseUrl);
  socket.onerror = function(error){
    console.log("Socket Error: " + error);
    //init_socket();
  };

  socket.onopen = function(){

    new QWebChannel(socket, function(channel){
      console.log("Connected");
      WebChannel.qt = channel;
      channel.objects.parser.message.connect(function (m){
        var c = document.getElementById("consola");
        c.innerHTML += "<p>" + m + "</p>";
        console.log(m);
      });
    });

  };

})();
