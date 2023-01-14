


// variables: F+-[]
// F = forward 
// + = turn right 
// - = turn left 
// [ = save state
// ] = restore state

// axiom: F
// rule(s) : F -> FF+[+F-F-F]-[-F+F+F] 

var axiom = "F";
var sentence = axiom;
var len = 100;
var angle;
var rules = [{a:"F", b:"FF+[+F-F-F]-[-F+F+F]"}];

function generate() {
  len *= 0.5;
  var new_sentence = "";
  for (var i = 0; i<sentence.length; i++) {
    var current = sentence.charAt(i);
    var found = false;
    for (var j = 0; j < rules.length; j++) {
      if (current == rules[j].a) {
        found = true;
        new_sentence += rules[j].b;
        break;
      }
    }
    if (!found) {
      new_sentence += current;
    }
  }
  sentence = new_sentence;
  createP(sentence);
  turtle();
}

function turtle() {
  background(51);
  resetMatrix();
  stroke(255, 100);
  translate(width / 2, height);
  for (var i = 0; i < sentence.length; i++) {
    var current = sentence.charAt(i);
    if (current == "F"){
      line(0, 0, 0, -len);
      translate(0, -len);
    } else if (current == "+") {
      rotate(angle);
    } else if (current == "-" ) {
      rotate(-angle);
    } else if (current == "[") {
      push();
    } else if (current == "]" ) {
      pop();
    } 
  }
} 

function setup() {
  createCanvas(400, 400);
  createP(sentence);
  background(51);
  angle = radians(25);
  turtle();
  var button = createButton("Generate");
  for (var n = 0; n < 4; n++) {
    generate();
  }
  //button.mousePressed(generate);
}
