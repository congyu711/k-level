import subprocess
import filecmp

while True:
    subprocess.Popen("./gen 2000 800 > data.in",shell=True).wait()
    subprocess.Popen("./klevel-bf && ./klevel-main",shell=True).wait()
    try:
        status = filecmp.cmp("!klevelmain.out", "!klevelbf.out")
        if status:
            print("files are the same")
        else:
            print("files are different")
            break
    except IOError:
        print("Error:"+ "File not found or failed to read")