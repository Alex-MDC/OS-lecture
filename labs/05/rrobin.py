import sys, getopt, random

def main(argv):
    quantum = random.randint(3, 5)
    print("Using a random quantum of: ", quantum)
    context_switch = 2
    execution_time = 0
    avg_turnaroundT= 0.0
    context_sw=0

    processes=[]
    for i in range(1, random.randint(4,8)):
        # random process time
        processes.append(random.randint(1,15))


    print("Number of processes: ", len(processes))
    print(processes)
    num_processes = len(processes)

    try:
        opts, args= getopt.getopt(argv,"hq:",["quantum_time="])
    except getopt.GetoptError:
        print ("rrobin.py -q <quantum time>")
        sys.exit(-1)
    for opt, arg in opts:
        if opt == '-h':
            print ("test.py -q <quantum time>")
            sys.exit()
        elif opt in ("-q", "--quantum_time"):
            quantum = int(arg)

    for process in processes:
        if process <= quantum:
            print("process executed!")
            execution_time+=process
            print("execution time " + str(execution_time))
        else:
            print("process interrupted, exceeds quantum")
            remain_time = process - quantum
            context_sw+=1
            print("time process executed: "+ str(quantum))
            execution_time+=quantum + context_sw
            print("executiom time " + str(execution_time))
            processes.append(remain_time)

        print(processes)
        print()

    avg_turnaroundT = float(execution_time)/float(num_processes)
    print("Using a random quantum of: ", quantum)
    print("Total context switches: " + str(context_sw))
    print("Avg turnaround time: " + str(avg_turnaroundT))
    print("Cost of switching: " + str(context_switch * context_sw))

if __name__ == "__main__":
    main(sys.argv[1:])

