import subprocess
import filecmp

subprocess.Popen("timeout 100 ./klevel-main",shell=True).wait()
subprocess.Popen("./klevel-bf",shell=True).wait()
try:
    status = filecmp.cmp("!klevelmain.out", "!klevelbf.out")
    if status:
        print("files are the same")
    else:
        print("files are different")
except IOError:
    print("Error:"+ "File not found or failed to read")