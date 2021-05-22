import os

def itrdir(path: str):
    farr = []
    for x in os.scandir(path):
        if x.path.endswith(".cpp"):
            farr.append(os.path.abspath(x.path))
        elif os.path.isdir(x.path):
            for g in itrdir(x.path):
                farr.append(g)
    return farr

def reccount(path: str):
    sumc = 0
    for x in os.scandir(path):
        if os.path.isfile(x.path):
            sumc += sum(1 for line in open(x.path))
        elif os.path.isdir(x.path):
            sumc += reccount(x.path)
    return sumc

if __name__ == "__main__":
    args = "-lreplxx"
    outp = "build/mayonnaise"

    if not os.path.exists("build"):
        os.mkdir("build")

    os.system("g++ " + ' '.join(itrdir("src")) + " -o " + outp + " " + args)
    print("Build complete. Total lines of code: " + str(reccount("src")))