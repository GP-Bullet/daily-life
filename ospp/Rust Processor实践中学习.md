## Rust Processor

关于所有权

另加内存分配



### 克隆

在 Rust 中，`clone()` 方法默认进行的是深拷贝（Deep Copy）。深拷贝意味着整个对象及其所有的数据都会被复制。

在 Rust 中，clone() 是克隆（拷贝）一个对象的方法。克隆创建了一个新的具有相同值的对象，使得每个对象都有独立的所有权。

除了 clone() 方法之外，还有其他相关的概念：

1. 克隆（Clone）：克隆是创建一个对象的副本，使得每个对象都具有独立的所有权。在 Rust 中，Clone trait 定义了 clone() 方法，允许类型实现自定义的克隆行为。通过实现 Clone trait，可以为自定义类型提供克隆能力。

2. 深拷贝（Deep Copy）与浅拷贝（Shallow Copy）：深拷贝是在克隆过程中连同内部的数据一起复制，使得新对象与原对象彻底分离。浅拷贝仅仅复制对象本身，对于由指针引用的数据，仍然共享相同的底层数据。
```rust
#[derive(Clone)]
struct Person {
    name: String,
    age: u32,
}

fn main() {
    let person1 = Person {
        name: "John".to_string(),
        age: 30,
    };

    let person2 = person1.clone();
    let person3 = person1;  
    
    println!("person1: {} - {}", person1.name, person1.age);// 编译错误：person1已经被移动
    println!("person2: {} - {}", person2.name, person2.age);
    println!("person3: {} - {}", person3.name, person3.age);
}
```
#### 移动Move，复制Copy



#### 悬挂引用

以下是一个悬挂引用的例子：

```rust
fn dangling_reference() -> &String {
    let s = String::from("hello");
    &s  // 返回了一个指向局部变量的引用
}

fn main() {
    let reference = dangling_reference();
    println!("{}", reference);
}
```
在上述代码中，我们定义了一个函数 dangling_reference，该函数返回一个指向局部变量 s 的引用。由于 s 是函数内部的局部变量，它在函数返回后将被销毁，但我们尝试返回了一个指向它的引用。

这将导致一个悬挂引用的问题，因为引用 reference 指向的数据已经无效。Rust 编译器会在编译时检测到这个问题，并阻止代码编译通过，产生一个错误：

```rust
error: `s` does not live long enough
 --> main.rs:2:6
  |
2 |     &s
  |      ^^ borrowed value does not live long enough
3 | }
  | - `s` dropped here while still borrowed
```
#### 自动释放

在 Rust 中，当变量所拥有的资源（比如堆上分配的数据）被释放后，该变量本身也被认为是无效的。这意味着变量会在资源被释放后变为无效状态。

在你提供的示例中，当局部变量 s 所拥有的堆上的字符串数据被释放后，本身 s 变为无效。这是因为 s 失去了存储的数据，并且在 Rust 的所有权模型中，无效的变量不能继续使用。

可以通过尝试在变量 s 之后使用它来验证这一点：

```rust
fn main() {
    let s: String = String::from("hello");
    drop(s);  // 显式释放 s 所拥有的堆上的资源

    println!("{}", s);  // 编译错误，无法使用无效的变量 s
}
```
在上述代码中，我们使用 drop 函数显式释放变量 s 所拥有的堆上资源。该函数用于模拟资源的手动释放。在调用 drop(s) 后，变量 s 变为无效。尝试在之后使用 s 会导致编译错误，因为它已经是无效的。

#### 自动构建trait

在我们的代码中，我们可能需要在不同地方使用 `Person` 对象的副本，而不是引用同一个对象。为了创建这些副本，我们可以手动实现 `Clone` trait 来提供克隆的功能，例如：

```rust
impl Clone for Person {
    fn clone(&self) -> Self {
        Person {
            name: self.name.clone(),
            age: self.age,
        }
    }
}
```

然而，为了简化此过程，我们可以使用 `#[derive(Clone)]`。这样，编译器将自动生成与手动实现相同的代码，如下所示：

```rust
#[derive(Clone)]
struct Person {
    name: String,
    age: u32,
}
```

`#[derive(Clone)]` 是 Rust 的一个派生属性（derivative attribute），用于自动为结构体或枚举类型生成实现 `Clone` trait 的代码。派生属性使得编译器能够根据类型的特定属性来自动生成代码。

在上述例子中，我们使用 `#[derive(Clone)]` 标记了 `Person` 结构体的定义。这样做告诉编译器自动生成 `Clone` trait 的实现代码，使得 `Person` 类型可以通过 `clone()` 方法进行克隆操作。

通过使用 `#[derive(Clone)]`，我们不再需要手动实现 `Clone` trait 的 `clone()` 方法，因为编译器会根据结构体的字段类型生成适当的克隆代码。这提供了一种简单且一致的方式来派生 `Clone` trait 的实现。

派生属性不仅适用于 `Clone` trait，还可用于其他常见的 Rust traits，例如 `Eq`, `PartialEq`, `PartialOrd`, `Ord`, `Debug` 等。通过使用派生属性，我们可以轻松地为类型自动生成相应的 trait 实现，减少了手动编写重复代码的工作量。

#### Trait（类似于抽象类）与方法

```rust
// 定义一个Trait
trait Printable {
    fn print(&self);
}

// 定义一个结构体
struct Person {
    name: String,
    age: u32,
}

// 在结构体中实现Trait的方法
impl Printable for Person {
    fn print(&self) {
        println!("Name: {}, Age: {}", self.name, self.age);
    }
}

// 定义一个结构体的方法
impl Person {
    fn say_hello(&self) {
        println!("Hello, my name is {}.", self.name);
    }
}

fn main() {
    let person = Person { name: String::from("Alice"), age: 30 };
    person.print(); // 调用Trait的方法
    person.say_hello(); // 调用结构体的方法
}
```

在上面的例子中，我们定义了一个Trait `Printable`，它定义了一个方法 `print`，该方法用于打印一个实现了该Trait的类型的信息。我们还定义了一个结构体 `Person`，它有两个字段 `name` 和 `age`。我们在 `Person` 结构体中实现了 `Printable` Trait 的 `print` 方法。我们还定义了一个 `Person` 结构体的方法 `say_hello`，它用于打印一个 `Person` 实例的问候语。

在 `main` 函数中，我们创建了一个 `Person` 实例 `person`，并分别调用了 `Printable` Trait 的 `print` 方法和 `Person` 结构体的 `say_hello` 方法。这两个方法的调用方式不同，但它们都是对 `Person` 实例的操作，因此它们都可以访问 `Person` 实例的字段和方法。这也是Trait和方法的一个重要区别：Trait定义了一组类型共有的行为，而方法则定义了一个类型的具体行为。

#### self,&self和&mut self

在 `increment` 方法中，我们使用了 `&mut self` 参数来获取一个可变的 `Counter` 引用。由于该引用是可变的，所以我们可以修改 `Counter` 实例的 `count` 字段。

在 `decrement` 方法中，我们使用了 `self` 参数来获取 `Counter` 实例的所有权。由于该方法获取了所有权，所以它可以修改 `Counter` 实例的状态，并返回一个新的实例。

在 `get_count` 方法中，我们使用了 `&self` 参数来获取一个不可变的 `Counter` 引用。由于该引用是不可变的，所以我们不能修改 `Counter` 实例的状态。
```rust

struct Counter {
    count: u32,
}

impl Counter {
    fn new() -> Counter {
        Counter { count: 0 }
    }

    fn increment(&mut self) {
        self.count += 1;
    }

    fn decrement(self) -> Counter {
        Counter { count: self.count - 1 }
    }

    fn get_count(&self) -> u32 {
        self.count
    }
}

fn main() {
    let mut counter = Counter::new();

    counter.increment();
    counter.increment();
    println!("The count is: {}", counter.get_count());

    let new_counter = counter.decrement();
    println!("The count is: {}", new_counter.get_count()); //所有权转移了
    
}
```





在 Rust 中，你可以使用方法来修改结构体的实例的值，但这并不是唯一的方式。你也可以直接修改结构体实例的字段，或者使用函数来修改结构体实例的值。



```rust
copy codestruct Counter {
    count: u32,
}

fn increment(counter: &mut Counter) {
    counter.count += 1;
}

fn main() {
    let mut counter = Counter { count: 0 };
    increment(&mut counter);
    println!("The count is: {}", counter.count);
}
```

#### 所有权和引用

```rust
struct Counter {
    count: u32,
}

impl Counter {
    fn new() -> Counter {
        Counter { count: 0 }
    }

    fn increment(&mut self) {
        self.count += 1;
    }

    fn decrement(self) -> Counter {
        Counter { count : self.count - 1 }
    }
    
    fn get_count(&self) -> u32 {
        self.count
    }
}

fn addcounter(counter:&mut Counter){
    counter.count+=1;
}

fn main() {
    let mut counter = Counter::new();

    counter.increment();
    println!("The count is: {}", counter.get_count());
    counter.increment();
    println!("The count is: {}", counter.get_count());
    counter.count+=1;
    println!("The count is: {}", counter.get_count());

    addcounter(&mut counter);
    println!("The count is: {}", counter.get_count());
    
    let new=Counter{count:counter.count+3};
    println!("The new is: {}", new.get_count());
    
    let new_counter = counter.decrement();//所有权已经没有了
    println!("The new count is: {}", new_counter.get_count());
    //println!("The count is: {}", counter.get_count());
}
```

 Rust 中，`self` 和 `&self` 用于引用方法所属类型的实例，而它们之间的区别在于它们获取实例的方式。如果方法需要获取实例的所有权并修改它，则应该使用 `self`。如果方法只需要访问实例的状态而不修改它，则应该使用 `&self`。



引用的含义   用于让程序员在不将拥有权转移给其他变量的情况下，让多个变量同时访问同一个值或对象。

#### Rust的引用和C语言的指针

在Rust和C语言中，打印引用或指针时的行为是不同的。在Rust中，打印引用时打印的是引用所指向的值，而不是引用本身的地址。而在C语言中，打印指针时打印的是指针本身的地址，而要打印指针所指向的值，需要使用指针解引用操作符 `*`。

这种差异是由于Rust和C语言的内存管理机制不同所导致的。在Rust中，引用是一种安全的指针，它们在编译时被检查以确保不会出现空指针或悬垂指针等问题。因此，Rust中的引用并不需要存储指针地址，而是直接存储引用所指向的值，以提高代码的可读性和安全性。

而在C语言中，指针是一种非常灵活但也非常危险的概念，它们可以指向任何内存地址，包括无效或未初始化的内存地址。因此，在C语言中，指针必须显式地存储指向的内存地址，并通过解引用操作符 `*` 来访问该地址上的值。

因此，Rust和C语言在处理引用和指针时存在一些差异，这些差异反映了它们在内存管理和安全性方面的不同设计哲学。

```rust
fn main() {
    let s1 = String::from("hello");
    let s2 = &s1;
    println!("s1 address is {:p}, s2 address is {:p}", &s1, s2);
}
```

在这个例子中，我们使用了 `&` 运算符来获取变量 `s1` 的指针地址，并通过 `{:p}` 格式化符号将其打印出来。同样地，我们也通过 `s2` 直接打印其指针所指向的值，而不是指针本身的地址

#### impl和struct

