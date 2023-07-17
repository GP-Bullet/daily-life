
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