trait Shape {
    fn area(&self) -> f64;
}

struct Circle {
    radius: f64,
}

impl Shape for Circle {
    fn area(&self) -> f64 {
        std::f64::consts::PI * self.radius * self.radius
    }
}

struct Rectangle {
    width: f64,
    height: f64,
}

impl Shape for Rectangle {
    fn area(&self) -> f64 {
        self.width * self.height
    }
}
fn total_area(shapes: &[&dyn Shape]) -> f64 {
    let mut total = 0.0;
    for shape in shapes {
        total += shape.area();
    }
    total
}
fn main() {
    let shapes: Vec<&dyn Shape> = vec![
        &Circle { radius: 1.0 },
        &Rectangle { width: 3.0, height: 4.0 },
        //&Circle { radius: 1.5 },
    ];
    let total = total_area(&shapes);
    println!("Total area: {}", total);
}