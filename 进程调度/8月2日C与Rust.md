8月2日



#### 指针与结构体

```c

struct list_elem {
   struct list_elem* prev; // 前躯结点
   struct list_elem* next; // 后继结点
};
/* 链表结构,用来实现队列 */
struct list {
/* head是队首,是固定不变的，不是第1个元素,第1个元素为head.next */
struct list_elem head;
/*tail是队尾,同样是固定不变的 */
struct list_elem tail;
};
/* 初始化双向链表list */
void list_init (struct list* list) {
   list->head.prev = NULL;
   list->head.next = &list->tail;
   list->tail.prev = &list->head;
   list->tail.next = NULL;
}
如何判断list到head是用.还是->，以及head到prev
```

>list是一个指向`struct list`的指针,所以访问它的成员需要使用->
head和tail是`struct list`中的成员,不是指针,所以访问它们的成员需要使用.





**帮我举例解释当C语言出现结构体套结构体的定义时，成员是否应该加*如何确定**
在C语言中，如果一个结构体中的成员是另一个结构体类型的变量，可以使用结构体指针来定义这个成员。具体来说，可以在结构体定义中使用指向另一个结构体的指针类型，例如：

```c
struct foo {
  int x;
};

struct bar {
  struct foo *ptr_foo;
};
```

在这个例子中，`bar`结构体中的`ptr_foo`成员是一个指向`foo`结构体的指针。这个指针可以指向任何类型为`foo`的变量，因为它指向的是`foo`结构体的地址，而不是`foo`结构体本身。

如果要访问`ptr_foo`指向的`foo`结构体中的成员，可以使用指针运算符`->`，例如：

```c
struct bar my_bar;
my_bar.ptr_foo = malloc(sizeof(struct foo));
my_bar.ptr_foo->x = 42;
```

在这个例子中，我们首先创建了一个`bar`类型的变量`my_bar`，然后动态分配了一个`foo`类型的变量，将其地址存储在`ptr_foo`中。最后，我们使用指针运算符`->`来访问`ptr_foo`指向的`foo`结构体中的`x`成员，并将其设置为42。

需要注意的是，在C语言中，当一个结构体中的成员是另一个结构体类型的变量时，是否需要使用指针类型作为成员类型取决于具体情况。**如果这个结构体中的成员是一个较大的结构体，或者需要在程序的多个部分中使用，那么使用指针类型作为成员类型可能更合适，因为这可以减少内存占用和复制成本**，**同时也更加灵活。如果这个结构体中的成员是一个较小的结构体，并且只在一个函数内使用，那么直接使用结构体类型作为成员类型也是可以的**。

>struct bar {
  struct foo ptr_foo;
};
如果这样定义应该如何使用

在这个例子中，`bar`结构体中的`ptr_foo`成员是一个`foo`类型的变量，而不是指向`foo`结构体的指针。这意味着，在定义`bar`类型的变量时，`ptr_foo`成员将会占据一定的内存空间，而不是仅仅存储一个指向`foo`结构体的地址。因此，在使用`ptr_foo`成员时，需要使用`.`运算符，而不是`->`运算符。

例如，假设我们有以下的结构体定义：

```c
struct foo {
  int x;
};

struct bar {
  struct foo ptr_foo;
};
```

我们可以创建一个`bar`类型的变量，并访问其`ptr_foo`成员，例如：

```c
struct bar my_bar;
my_bar.ptr_foo.x = 42;
```

在这个例子中，我们首先创建了一个`bar`类型的变量`my_bar`，然后使用`.`运算符来访问`ptr_foo`成员中的`x`成员，并将其设置为42。

需要注意的是，与使用指针类型作为结构体成员相比，直接使用结构体类型作为成员类型可能会导致内存占用和复制成本较高，因为每个`bar`类型的变量都会包含一个完整的`foo`类型的变量。因此，在设计结构体时，应该根据具体情况选择适当的成员类型。

#### Rust dyn

```
impl DowncastArc for dyn IndexNode {
    fn as_any_arc(self: Arc<Self>) -> Arc<dyn Any> {
        self
    }
}
impl ... for ...是什么意思，另外dyn是什么意思
```



>`impl`是Rust语言中的关键字，用于实现trait或者某个类型的方法。在给定的代码示例中，`impl DowncastArc for dyn IndexNode`表明为实现`DowncastArc`trait，针对`dyn IndexNode`这个动态类型来定义具体的方法。这个方法是`as_any_arc`，它将`Arc<Self>`转换为`Arc<dyn Any>`类型。

> 在Rust中，`dyn`是关键字，用于指示一个类型是动态分发（dynamic dispatch）的，也就是说，它是通过trait object实现的。这意味着这个类型在编译期间不确定，只有在运行时才能确定。在给定的代码示例中，`dyn IndexNode`表示一个实现了`IndexNode` trait的类型，但具体的类型在编译期间不确定，只有在运行时才能确定。

下面是一个简单的例子，用于说明如何使用trait object实现多态性。假设我们有一个几何图形的类层次结构，其中包含了不同类型的几何图形，例如圆形（Circle）和矩形（Rectangle），每种几何图形都有一个计算面积的方法。我们可以定义一个trait `Shape`来表示这个特征，并在每个几何图形中实现这个trait。

```rust
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
```

现在我们想要编写一个函数，该函数可以计算不同类型几何图形的总面积。我们可以使用trait object来实现这个函数：

```rust
fn total_area(shapes: &[&dyn Shape]) -> f64 {
    let mut total = 0.0;
    for shape in shapes {
        total += shape.area();
    }
    total
}
```

在这个函数中，我们使用一个`&[&dyn Shape]`类型的参数来接受几何图形的数组。这个数组中的每个元素都是一个对实现`Shape` trait的具体类型的引用。我们可以使用`for`循环遍历这个数组，并对每个元素调用`area`方法，计算它的面积，并将结果累加到总面积中。

现在，我们可以创建一些具体的几何图形实例，并将它们传递给`total_area`函数，以计算它们的总面积：

```rust
fn main() {
    let shapes: Vec<&dyn Shape> = vec![
        &Circle { radius: 2.0 },
        &Rectangle { width: 3.0, height: 4.0 },
        &Circle { radius: 1.5 },
    ];
    let total = total_area(&shapes);
    println!("Total area: {}", total);
}
```

在这个示例中，我们创建了一个包含三个几何图形的数组，其中包括两个圆和一个矩形。我们将这个数组传递给`total_area`函数，计算它们的总面积，并将结果打印到控制台上。由于我们使用trait object来实现这个函数，它可以处理不同类型的几何图形，并且可以在运行时动态地确定它们的类型。





#### Box<&str> 和 &str

使用 `Box<&str>` 的场景：

1. 当需要在堆上动态分配一个字符串并且需要在不同的函数中传递该字符串时，可以使用 `Box<&str>`。
2. 当需要在字符串上进行修改时，可以使用 `Box<&str>` 指向堆上分配的字符串数据。

使用 `&str` 的场景：

1. 当只需要读取字符串数据时，可以使用 `&str` 引用类型，这可以提高性能并避免不必要的内存分配。
2. 当需要在一个函数内部传递字符串数据时，可以使用 `&str` 引用类型。

使用 `String` 的场景：

1. 当需要动态地创建、修改和拼接字符串时，可以使用 `String` 类型。
2. 当需要将一个 `&str` 类型的字符串转换为字符串类型时，可以使用 `String::from()` 方法。
3. 当需要将一个字符串类型的字符串转换为 `&str` 类型时，可以使用 `&s[..]` 或 `s.as_str()` 方法。

#### 元组

`(self.find(".")?, String::from(path))` 是一个元组（tuple），它包含了两个元素。

第一个元素是 `self.find(".")?`，这是一个函数调用表达式，它会在 `self` 目录中查找名称为 "." 的文件或目录，如果查找成功，返回该文件或目录的 inode，否则返回一个 `Err` 类型的错误值。在这个元组中，`self.find(".")?` 的返回值会被绑定到元组的第一个元素上。

第二个元素是 `String::from(path)`，这是一个创建 `String` 类型对象的表达式，它会将 `path` 转换为 `String` 类型。在这个元组中，`String::from(path)` 的返回值会被绑定到元组的第二个元素上。

逗号 `,` 用于分隔元组中的元素。在这个元组中，逗号表示将两个表达式的返回值组合成一个元组。

这个元组的执行顺序是从左到右依次执行表达式，然后将它们的返回值组合成元组。因为这是一个元组表达式，所以整个表达式的返回值就是这个元组。
