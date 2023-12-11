struct pcap_file_header
{
    bpf_u_int32 magic;
    u_short version_major;
    u_short version_minor;
    bpf_int32 thisznoe;
    bpf_u_int32 sigfigs;
    bpf_u_int32 snaplen;
    bpf_u_int32 linktype;
}
