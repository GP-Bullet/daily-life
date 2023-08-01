pub struct ProcessBasicInfo {
    cwd: String,
}

impl ProcessBasicInfo {
    pub fn new() -> Self {
        Self {
            cwd: String::from("fdfd"),
        }
    }

    pub fn path(&self) -> String {
        self.cwd.clone()
    }

    pub fn set_path(&mut self, path: String) {
        self.cwd = path;
    } 
}

fn normalize_path(proc: &mut ProcessBasicInfo, path: &str) {
    if path.len() > 0 {
        let cwd = match path.as_bytes()[0] {
            b'/' => String::from("/"),
            _ => proc.path(),
        };
        let mut cwd_vec: Vec<_> = cwd.split("/").filter(|&x| x != "").collect();
        let path_split = path.split("/").filter(|&x| x != "");
        for seg in path_split {
            if seg == ".." {
                cwd_vec.pop();
            } else if seg == "." {
                // 当前目录
            } else {
                cwd_vec.push(seg);
            }
        }
        proc.set_path(String::from(""));
        let mut new_path=String::from("");
        for seg in cwd_vec {
            new_path.push_str("/");
            new_path.push_str(seg);
        }
        proc.set_path(String::from(new_path));
        if proc.path() == "" {
            proc.set_path(String::from("/"));
        }
    }
}

fn main() {
    let mut proc = ProcessBasicInfo::new();
    let path = "/usr/local/../bin/./program";
    println!("path: {}", proc.path());
    normalize_path(&mut proc, path);

    println!("Normalized path: {}", proc.path());
}