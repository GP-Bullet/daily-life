struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    // 该方法获取 Rectangle 实例的所有权
    fn area(self) -> u32 {
        self.width * self.height
    }

    // 该方法获取 Rectangle 实例的不可变引用
    fn perimeter(& self) -> u32 {
        (self.width+1) * self.height
    }
}

fn main() {
    let rect = Rectangle { width: 10, height: 20 };

    // 使用 area 方法获取 Rectangle 实例的所有权
    let area = rect.area();
    println!("The area of the rectangle is {} square pixels.", area);

    // 使用 perimeter 方法获取 Rectangle 实例的不可变引用
    let perimeter = rect.perimeter();
    println!("The perimeter of the rectangle is {} pixels.", perimeter);
}