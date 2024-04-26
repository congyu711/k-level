import subprocess
import filecmp
from alive_progress import alive_bar
N=100
with alive_bar(N) as bar:
    for K in range(N):
        subprocess.Popen("./gen 10000 1000 > data.in",shell=True).wait()
        subprocess.Popen("timeout 100 ./klevel-main",shell=True).wait()
        subprocess.Popen("./klevel-bf",shell=True).wait()
        try:
            status = filecmp.cmp("!klevelmain.out", "!klevelbf.out")
            if status:
                print("files are the same")
            else:
                print("files are different")
                break
        except IOError:
            print("Error:"+ "File not found or failed to read")
        bar()