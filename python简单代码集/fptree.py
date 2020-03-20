from typing import Iterator, Tuple
import sys
import copy

dict = {}
data = []
support = 0.005
maxsetcount = 2
tree = []
head = []
flist = []
f = []

def readLines(path: str) -> Iterator[str]:
	with open(path, 'r') as f:
		for line in f.read().split("\n"):
			yield line

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
	for i in list(dict):
		if dict[i] < length * support:
			dict.pop(i)	
		i += 1	
		
	for i in dict:
		tmp = [i, dict[i], None]
		head.append(tmp)		#[ch, fre, next]
		dict[i] = round(dict[i] / length, 4)	
#	print(dict)
	
	for i in dict:
		tmp = [i, dict[i]]
		f.append(tmp)

	f = sorted(f, key = lambda x: x[1], reverse = True)
	head = sorted(head, key = lambda x: x[1], reverse = True)
	tmp = {}
	
	for index, i in enumerate(f):
		tmp[i[0]] = index
		flist.append(i[0])
		
	f = tmp
	print(f)
	print()
	print(flist)
	print()
	
	s = []
	for i in data:
		k = []
		for j in i:
			if j in f:
				k.append(j)
		k = sorted(k, key = lambda x: f[x])
		if len(k) > 1:
			s.append(k)

	data = s	#一遍扫描获取filtered and sorted transactions

	tree.append([None, None, [], None, None]) #[char, fre, [next(坐标)], nextch, pre]
	
	for i in data:
		p = 0
		for j in i:
			flag = False
			for k in tree[p][2]:
				if tree[k][0] == j:		#找到了
					tree[k][1] += 1
					p = k
					flag = True
					break
			if not flag:				#如果没找到
				tree.append([j, 1, [], None, p])
				tree[p][2].append(len(tree) - 1)
				#连接字符线
				pos = flist.index(j)
				if head[pos][2] != None:
					tmp = head[pos][2]
					while tree[tmp][3] != None:
						tmp = tree[tmp][3]
					tree[tmp][3] = len(tree) - 1
				else:
					head[pos][2] = len(tree) - 1

#	print(head)
#	for index, i in enumerate(tree):
#		print(index, i)
	
	ans = [[] for i in range(10)]
	for i in head:
		pos = i[2]
		newfp = []
		while pos != None:
			n = tree[pos][1]
			p = tree[pos][4]
			lst = []
			while p != 0:
				lst.append(tree[p][0])
				p = tree[p][4]
			pos = tree[pos][3]
			
			lst.append(n)
			lst = list(reversed(lst))
			
			if len(lst) > 1:
				newfp.append(lst)
		
		count = [0 for i in range(len(flist))]
		flag = [True for i in range(len(flist))]
		
		for indexj, j in enumerate(newfp):
			for k in j[1:]:
				count[flist.index(k)] += newfp[indexj][0]
		
		for indexj, j in enumerate(count):
			if j < length * support:
				flag[indexj] = False
				
#		print(count)
#		print(flag)	
		
		q = []
		for j in newfp:
			tmp = [j[0]]
			for k in j[1:]:
				if flag[flist.index(k)]:
					tmp.append(k)
			if len(tmp) > 1:
				q.append(tmp)
		
		newfp = q
#		print("newfp =", newfp)
#		print()
		
		newtmp = []
		for indexj, j in enumerate(newfp):
			t = copy.deepcopy(j)
			t[0] = 0
			for indexk, k in enumerate(newfp):
				tmp = []
				for kk in k[1:]:
					if kk in j[1:]:
						tmp.append(kk)
				if tmp == j[1:]:		#j属于k
					t[0] += k[0]
			if t not in newtmp:
				newtmp.append(t)
		
		for j in newtmp:
			j.append(i[0])
			
		newfp = newtmp
		
		tmp = []
		for j in newfp:
			if j[0] >= support * length:
				tmp.append(j)
		
		newfp = tmp
		
#		print(newfp)
#		print()
#		print()
		
		for j in newfp:
			'''
			if len(j) > maxsetcount + 1:
				ans = []
				maxsetcount += 1
				j[0] = round(j[0] / length, 4)
				if j[1:] not in ans:
					ans.append((sorted(j[1:]), j[0]))
			elif len(j) == maxsetcount + 1:
				j[0] = round(j[0] / length, 4)
				if j[1:] not in ans:
					ans.append((sorted(j[1:]), j[0]))
			'''
			j[0] = round(j[0] / length, 4)
			if j[1:] not in ans[len(j)]:
				ans[len(j)].append([j[1:], j[0]])
	
	
	print("support =", support)
	print(len(dict))
	maxsetcount = 1
	count = 0
	for i in ans:
		if len(i) != 0:
			maxsetcount += 1
			print(len(i))
			count += len(i)
			print(i)
	print("寻找不小于x项集 =", maxsetcount)
	count += len(dict)
	print(count)
#	print(ans)