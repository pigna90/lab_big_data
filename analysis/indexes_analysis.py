import matplotlib.pyplot as plt
import seaborn

##
# Read queries times results from file and returns a map for each indexes.
##
# times_fnmae - file name of a file created with run_all_queries.sh > results_file
##
def read_results(times_fname):
	baseline = {}
	index1 = {}
	perc = 0
	k = 0

	with open(times_fname, "r") as f:
		for line in f:
			if("Baseline" in line):
				main_map = baseline
			elif("Index1" in line):
				main_map = index1
			if("Baseline" not in line and "Index1" not in line and "-----" not in line):
				if("queries" in line):
					elem = line.replace(".", "-").split("-")
					perc = int(elem[len(elem)-3])
					k = int(elem[len(elem)-2])
				else:
					elem = line.replace("\t", " ").split(" ")
					value = int(elem[len(elem)-4])
					if perc not in main_map:
						main_map[perc] = {k : {"range" : value}}
					else:
						#main_map[perc][k] = value
						if k not in main_map[perc]:
							main_map[perc][k] = {"range" : value}
						else:
							main_map[perc][k]["topk"] = value

	return {"baseline" : baseline, "index1" : index1}

##
# Plot of range times
##
def plot_range(res):
	for key in res:
		index = res[key]
		x = []
		y = []
		for perc in index:
			x.append(perc)
			y.append(index[perc][1]["range"])
		plt.plot(x, y)

	plt.title("Range Results")
	plt.xlabel("% date range")
	plt.ylabel("Time (ns)")
	plt.legend(res.keys(), loc='upper left')
	plt.show()

##
# Plot of topK times
##
def plot_topk(res):
	percs = list(next(iter (res.values())).keys())

	for perc in percs:
		for key in res:
			index = res[key]
			x = []
			y = []
			for k in index[perc]:
				x.append(int(k))
				y.append(index[perc][k]["topk"])
			plt.plot(x, y)

		plt.title("TopK Results - "+ str(perc) + "% date range")
		plt.xlabel("K")
		plt.ylabel("Time (ns)")
		plt.legend(res.keys(), loc='upper left')
		plt.show()

def main(args):
	res = read_results(args[1])

	plot_range(res)
	plot_topk(res)

	return 0

if __name__ == '__main__':
	import sys
	sys.exit(main(sys.argv))
