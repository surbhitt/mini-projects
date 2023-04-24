
var slider;
function setup() {
  createCanvas(500, 500);
  slider = createSlider(0, TWO_PI, PI/4, 0.01)

}

function draw() {
  background(51);
  translate(250, height)
  stroke(255);
  angle = slider.value()
  branch(100)
}

function branch(len) {
  line(0, 0, 0, -len)
  translate(0, -len)
  if (len > 7) {
    push();
    rotate(angle * 0.8);
    branch( len * 0.70)
    pop();
    push();
    rotate(-angle);
    branch( len * 0.67)
    pop();
  }
}

/*
var slider;
function setup() {
  createCanvas(500, 500);
  slider = createSlider(0, TWO_PI, PI/4, 0.01)

}

function draw() {
  background(51);
  translate(250, height)
  stroke(255);
  angle = slider.value()
  branch(100)
}

function branch(len) {
  line(0, 0, 0, -len)
  translate(0, -len)
  if (len > 4) {
    push();
    rotate(angle);
    branch( len * 0.67)
    pop();
    push();
    rotate(-angle);
    branch( len * 0.67)
    pop();
  }
}
*/



