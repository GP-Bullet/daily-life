pub struct ProcessBasicInfo {
    cwd: String,
}

impl ProcessBasicInfo {
    pub fn new() -> Self {
        Self {
            cwd: String::from("fdfd"),
        }
    }

    pub fn get_path(&self) -> String {
        self.cwd.clone()
    }

    pub fn append_to_path(&mut self, additional: &str) {
        self.cwd.push_str(additional);
    }
}

fn normalize_path(proc: &mut ProcessBasicInfo, path: &str) {
    if path.len() > 0 {
        let cwd = match path.as_bytes()[0] {
            b'/' => String::from("/"),
            _ => proc.cwd.clone(),
        };
        let mut cwd_vec: Vec<_> = cwd.split("/").filter(|&x| x != "").collect();
        let path_split = path.split("/").filter(|&x| x != "");
        for seg in path_split {
            if seg == ".." {
                cwd_vec.pop();
            } else if seg == "." {
                // nothing to do here.
            } else {
                cwd_vec.push(seg);
            }
        }
        proc.get_path() = String::from("");
        for seg in cwd_vec {
            proc.append_to_path("/");
            proc.append_to_path(seg);
        }
        if proc.cwde == "" {
            proc.cwd = String::from("/");
        }
    }
}

fn main() {
    let mut proc = ProcessBasicInfo::new();
    let path = "/usr/local/../bin/./program";

    normalize_path(&mut proc, path);

    println!("Normalized path: {}", proc.get_path());
}