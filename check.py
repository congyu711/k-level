import subprocess
import filecmp

while True:
    subprocess.Popen("./gen 50000 > data.in && ./klevel-bf < data.in && ./klevel-main < data.in",shell=True).wait()
    try:
        status = filecmp.cmp("!klevelmain.out", "!klevelbf.out")
        if status:
            print("files are the same")
        else:
            print("files are different")
            break
    except IOError:
        print("Error:"+ "File not found or failed to read")