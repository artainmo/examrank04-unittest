import os
import sys
import subprocess
from termcolor import colored

os.chdir(os.getcwd() + "/microshell")
microshell_path = os.getcwd() + "/microshell.a"

def show_result(result, fd_error, fd_correct, fd_verify, test, number, output_m, output_b):
    if number > 22:
        print(test, end="")
        print(colored("VERIFY", "yellow") + "\n")
        fd_verify.write("\n****************************************\ncommand:\n%s\n****************************************\n" % (test))
        fd_verify.write("==========output==========\nYOU:\n%s\n" % (output_m))
    elif result:
        print(test, end="")
        print(colored("CORRECT", "green") + "\n")
        fd_correct.write("\n****************************************\ncommand:\n%s\n****************************************\n" % (test))
        fd_correct.write("==========output==========\nYOU:\n%s\nBASH:\n%s" % (output_m, output_b))
    else:
        print(test, end="")
        print(colored("WRONG", "red") + "\n")
        fd_error.write("\n****************************************\ncommand:\n%s\n****************************************\n" % (test))
        fd_error.write("==========output==========\nYOU:\n%s\nBASH:\n%s" % (output_m, output_b))

def test_microshell(cmd):
    try:
        output = subprocess.run([microshell_path + " " + cmd], shell=True, capture_output=True, encoding="utf-8", executable="/bin/zsh", timeout=1)
    except:
        print("microshell test error")
        quit()
    if output.returncode != 0:
        return "crash"
    return output.stderr + output.stdout

def test_bash(cmd):
    cmd = cmd.replace('"', '')
    try:
        output = subprocess.run([cmd], shell=True, capture_output=True, encoding="utf-8", executable="/bin/bash", timeout=1)
    except:
        print("microshell test error")
        quit()
    return output.stderr + output.stdout

def launch_test(test, number, fd_error, fd_correct, fd_verify):
    output_m = test_microshell(test)
    output_b = test_bash(test)
    show_result(output_m == output_b, fd_error, fd_correct, fd_verify, test, number, output_m, output_b)

if __name__ == "__main__":
    try:
        os.remove("../logs/error.txt")
        os.remove("../logs/correct.txt")
        os.remove("../logs/verify.txt")
    except:
        pass
    if os.path.isfile(microshell_path) == 0:
        print("ERROR: minishell.a executable/path")
        quit()
    with open("../tester/tests.txt", "r") as fd_tests, open("../logs/error.txt", "a+") as fd_error, open("../logs/correct.txt", "a+") as fd_correct, open("../logs/verify.txt", "a+") as fd_verify:
        tests = fd_tests.readlines()
        for number, test in enumerate(tests):
            launch_test(test, number, fd_error, fd_correct, fd_verify)
    print("\n")
