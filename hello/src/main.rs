use std::sync::{Mutex, Arc};
use std::collections::BTreeMap;

pub struct ProcessGroupManager(pub Arc<Mutex<BTreeMap<usize, Vec<usize>>>>);

impl ProcessGroupManager {
    pub fn new() -> Self {
        Self(Arc::new(Mutex::new(BTreeMap::new())))
    }

    // pub fn add_process(&self, pgid: usize, pid: usize) {
    //     let mut inner = self.0.lock().unwrap();
    //     let vec = inner.get(&pgid).cloned().unwrap_or_else(Vec::new);
    //     inner.insert(pgid, vec![pid]);
    // })))
    }

    // pub fn add_process(&self, pgid: usize, pid: usize) {
    //     let mut inner = self.0.lock().unwrap();
    //     let vec = inner.get(&pgid).cloned().unwrap_or_else(Vec::new);
    //     inner.insert(pgid, vec![pid]);
    // }
    pub fn add_process(&self, pgid: usize, pid: usize) {
        let mut inner = self.0.lock().expect("无法获取锁");
        if let Some(vec) = inner.get_mut(&pgid) {
            vec.push(pid);
        } else {
            let mut vec = Vec::new();
            vec.push(pid);
            inner.insert(pgid, vec);
        }
    }

    pub fn add_group(&self, pgid: usize) {
        let mut inner = self.0.lock().unwrap();
        inner.insert(pgid, Vec::new());
    }
    pub fn add_process(&self, pgid: usize, pid: usize) {
        let mut inner = self.0.lock().expect("无法获取锁");
        if let Some(vec) = inner.get_mut(&pgid) {
            vec.push(pid);
        } else {
            let mut vec = Vec::new();
            vec.push(pid);
            inner.insert(pgid, vec);
        }
    }

    pub fn add_group(&self, pgid: usize) {
        let mut inner = self.0.lock().unwrap();
        inner.insert(pgid, Vec::new());
    }

    pub fn get_group_by_pgid(&self, pgid: usize) -> Option<Vec<usize>> {
        self.0.lock().unwrap().get(&pgid).cloned()
    }

    pub fn set_pgid_by_pid(&self, pid: usize, new_pgid: usize, old_pgid: usize) {
        let mut inner = self.0.lock().unwrap();
        if let Some(old_group_vec) = inner.get_mut(&old_pgid) {
            old_group_vec.retain(|&x| x != pid);
        } else {
            panic!("pid {} not found in old_pgid {}", pid, old_pgid);
        }
        let new_group_vec = inner.entry(new_pgid).or_insert_with(Vec::new);
        new_group_vec.push(pid);
    }
}

pub fn main() {
    let process_group_manager = ProcessGroupManager::new();


    process_group_manager.add_process(1, 100);
    process_group_manager.add_process(2, 300);
    process_group_manager.add_process(100,100);
    process_group_manager.add_process(1, 200);

    let group1_processes = process_group_manager.get_group_by_pgid(1);
    if let Some(processes) = group1_processes {
        let processes_str = processes.iter().map(|&x| x.to_string()).collect::<Vec<String>>().join(", ");
        println!("Group 1 processes: {}", processes_str);
    } else {
        println!("Group 1 not found");
    }

    let group2_processes = process_group_manager.get_group_by_pgid(2);
    println!("Group 2 processes: {:?}", group2_processes);

    process_group_manager.set_pgid_by_pid(600, 3, 1);

    let group1_processes_updated = process_group_manager.get_group_by_pgid(1);
    println!("Group 1 processes updated: {:?}", group1_processes_updated);

    let group2_processes_updated = process_group_manager.get_group_by_pgid(2);
    println!("Group 2 processes updated: {:?}", group2_processes_updated);

    let group1_processes_updated = process_group_manager.get_group_by_pgid(3);
    println!("Group 3 processes updated: {:?}", group1_processes_updated);

    let group1_processes_updated = process_group_manager.get_group_by_pgid(100);
    println!("Group 100 processes updated: {:?}", group1_processes_updated);
}