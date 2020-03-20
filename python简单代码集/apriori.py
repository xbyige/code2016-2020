from typing import Iterator, Tuple
import sys
import time

dict = {}
data = []
dpos = []
support = 0.01
supportcount = 0
length = 0

def readLines(path: str) -> Iterator[str]:
	with open(path, 'r') as f:
		for line in f.read().split("\n"):
			yield line

def Apriori(n, tmp):
	print(tmp)
	fset = []
	for i in tmp:
		for j in tmp:
			s = i.union(j)
			if len(s) == n:
				f = True
				for k in range(len(s)):
					p = list(s)
					x = set(p[:k] + p[k+1:])
					if x not in tmp:
						f = False
						break
				if f:
					fset.append(s)

	#以下重写
	'''
	tmp = []
	for indexi, i in enumerate(fset):
		i = sorted(list(i))
		if i not in tmp:
			tmp.append(i)
			
	fset = tmp
	fcount = [0 for i in range(len(fset))]
		
	for index, i in enumerate(fset):
		p = 0
		ppos = 0
		while p < len(data):
			if i[0] < data[p][0]:
				break
			fl = True
			for j in i:
				if j not in data[p]:
					fl = False
					break
			if fl:
				fcount[index] += 1
			p += 1
	'''
	
	pos = []
	kkk = sorted(list(i))
	kkk = kkk[0]
	tmp = []
	for indexi, i in enumerate(fset):
		i = sorted(list(i))
		if i not in tmp:
			tmp.append(i)
			if kkk != i[0]:
				kkk = i[0]
				pos.append(tmp.index(i))
			
	pos.append(99999999)

	fset = tmp
	
	fcount = [0 for i in range(len(fset))]
	
	for indexj, j in enumerate(data):
		p = 0
		ppos = 0
		ma = max(j)
		while p < len(fset):
			if fset[p][0] not in j:
				if fset[p][0] > ma:
					break
				while pos[ppos] <= p:
					ppos += 1
				p = pos[ppos]
				continue
				
			if n == 2:
		#		if fset[p][1] < j[]
				if fset[p][1] in j:
					fcount[p] += 1
					if len(j) == 2:
						j = []
			else:
				fl = True
				for i in fset[p][1:]:
					if i not in j:
						fl = False
						break
				if fl:
					fcount[p] += 1
					if len(j) <= n:
						j = []
	
			p += 1
	
	
	tmp = []

	for index, i in enumerate(fset):
		t = [i, round(fcount[index] / length, 4)]
		tmp.append(t)
			
#	print(tmp)
	fset = tmp
	tmp = []
	for i in fset:
		if i[1] >= support:
			tmp.append(set(i[0]))
	
	return tmp

if __name__ == '__main__':
	print("support =", support)
	path = 'retail.dat'
	for line in readLines(path):
		l = line.split(" ")[:-1]
		for j in range(len(l)):
			l[j] = int(l[j])
		data.append(l)
		for i in l:
			if i not in dict:
				dict[i] = 1
			else:
				dict[i] += 1
	
	length = len(data)
	supportcount = support * length
	
	for i in list(dict):
		if dict[i] < supportcount:
			dict.pop(i)	
		i += 1	
		
	for i in dict:
		dict[i] = round(dict[i] / length, 4)	
	print(len(dict))
	
	fset = []
	tmp = []
	tmp1 = []
	for i in dict:
		tmp.append({i})
		tmp1.append(i)
	
	s = []
	for i in data:
		k = []
		for j in i:
			if j in tmp1:
				k.append(j)
		if len(k) > 1:
			s.append(k)

	s.sort(key=lambda x:(x[0], x[1]))
	data = s
#	print(len(s))
	t = 0
	
	'''
	time_s = time.time()
	tmp2 = []
	for i in data:
		if i not in tmp2:
			tmp2.append(i)

	print(len(tmp2))
	time_e = time.time()
	print(time_e - time_s)
	'''
	
	
	'''
	kkk = -1
	for i in data:
		if kkk != i[0]:
			kkk = i[0]
			dpos.append(data.index(i))
			
	dpos.append(99999999)
	print(dpos)
	'''
	
	n = 2
	count = 0
	while True:
		if len(tmp) < 1:
			break
		elif len(tmp) == 1:
			print()
			count += len(tmp)
	#		print(tmp)
			break
		tmp = Apriori(n, tmp)
#		print()
		count += len(tmp)
		print(len(tmp))
		n = n + 1

	count += len(dict)
	print(count)