
    pub fn search_insert(nums: Vec<i32>, target: i32) -> i32 {
        let n = nums.len();
        if n == 0 || nums[0] >= target {
            return 0;
        }
        if nums[n - 1] < target {
            return n as i32;
        }
        let mut left = 0;
        let mut right = n - 1;
        while left <= right {
            let mid = (left + right) >> 1;
            if nums[mid] == target {
                return mid as i32;
            } else if nums[mid] < target {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        left as i32
    }


use std::io;

fn main() {
    // 提示用户输入数组长度和元素
    println!("请输入数组的长度：");
    let mut n_str = String::new();
    io::stdin().read_line(&mut n_str).expect("读取输入失败");
    let n: usize = n_str.trim().parse().expect("请输入非负整数");

    let mut nums = vec![];
    println!("请依次输入数组的元素：");
    let mut elem_str = String::new();
    io::stdin().read_line(&mut elem_str).expect("读取输入失败");
    for elem in elem_str.split_whitespace() {
        let num: i32 = elem.parse().expect("请输入整数");
        nums.push(num);
    }

    // 提示用户输入目标数
    println!("请输入目标数：");
    let mut target_str = String::new();
    io::stdin().read_line(&mut target_str).expect("读取输入失败");
    let target: i32 = target_str.trim().parse().expect("请输入整数");

    // 调用 Solution::search_insert 方法查询插入位置
    let result = search_insert(nums, target);

    // 输出结果
    println!("插入目标数的下标为：{}", result);
}