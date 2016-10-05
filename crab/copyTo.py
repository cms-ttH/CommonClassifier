import os, subprocess, sys


def xrdfs(server, cmd):
    ret = subprocess.Popen(
        ["xrdfs", server] + cmd,
        stdout=subprocess.PIPE
    ).communicate()
    print ret[0]

def copy(infile, target_dir):
    fn = os.path.basename(infile)
    ret = subprocess.Popen(
        ["xrdcp", infile, target_dir + "/" + fn], 
        stdout=subprocess.PIPE
    ).communicate()
    print ret[0]

if __name__ == "__main__":
    server = "eoscms.cern.ch"
    target_dir = "/store/group/phys_higgs/hbb/mem/MEMInputTrees_ICHEP_V3newttsl"
    

    infiles = sys.argv[1:]

    xrdfs(server, ["mkdir", target_dir])
    for infile in infiles:
        copy(infile, "root://" + server + "/" + target_dir)
    xrdfs(server, ["ls", target_dir])
