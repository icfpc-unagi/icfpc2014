var tile_size = 0;
var signature_x = 0, signature_y = 0;
var tile_signature = new Array(100);
var tile_id = {};
var debug = "";

function GetSignature(image, x, y) {
  var signature = 0;
  for (var dy = 0; dy < 2; dy++) {
    for (var dx = 0; dx < 2; dx++) {
      for (var color = 0; color < 3; color++) {
        var d = image.data[((y + dy) * image.width + (x + dx)) * 4 + color];
        signature = (signature + (signature >> 1)) & 65535;
        signature = (signature + d) & 65535;
      }
    }
  }
  return signature;
}

function LoadMap() {
  var maze = document.getElementById('maze');
  var ctx = maze.getContext('2d');
  var pixels = ctx.getImageData(0, 0, maze.width, maze.height);
  var map = "";
  for (var y = 0; y < Math.floor(pixels.height / tile_size); y++) {
    for (var x = 0; x < Math.floor(pixels.width / tile_size); x++) {
      var c = parseInt(
          tile_id[GetSignature(pixels, x * tile_size, y * tile_size)]);
      switch (c) {
        case 0: c = '#'; break;
        case 1: c = ' '; break;
        case 2: c = '.'; break;
        case 3: c = 'o'; break;
        case 4: c = '%'; break;
        case 5: c = '\\'; break;
        case 6: c = 'X'; break;
        case 7: c = '0'; break;
        case 8: c = '1'; break;
        case 9: c = '2'; break;
        case 10: c = '3'; break;
        case 11: c = '4'; break;
        case 12: c = ':'; break;
        default: c = '?'; break;
      }
      map += c;
    }
    map += "\n";
  }
  debug += map + "\n";
  console.log(map);
}

function Record() {
  var score = document.getElementById('score').innerText - 0;
  var lives = document.getElementById('lives').innerText - 0;
  var ticks = document.getElementById('ticks').innerText - 0;
  debug += score + " " + lives + " " + ticks + "\n";
  LoadMap();
}

function HackInit() {
  var image = new Image();
  image.addEventListener('load', function() {
    var canvas = document.createElement('canvas');
    canvas.id = 'hack_tile';
    canvas.width = image.width;
    canvas.height = image.height;
    tile_size = image.height;
    var ctx = canvas.getContext('2d');
    ctx.drawImage(image, 0, 0);
    var pixels = ctx.getImageData(0, 0, image.width, image.height);
    for (var i = 0; i < image.width / image.height; i++) {
      var signature = GetSignature(pixels, i * tile_size, 0);
      if (tile_id[signature]) {
        console.log("signature already exists.");
      }
      tile_id[signature] = i;
    }
  });
  image.src = 'images/alltiles.png';
}

function HackRun() {
  Record();
  for (var i = 0; i < 999; i++) {
    HackStep();
    if (document.getElementById('status').innerText != 'Game running' &&
        document.getElementById('status').innerText != 'Single step') {
      break;
    }
  }
  var element = document.createElement('textarea');
  var body = document.getElementsByTagName("body").item(0);
  body.appendChild(element);
  element.value = debug;
}

function HackStep() {
  step();
  Record();
}
