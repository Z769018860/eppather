#!/usr/bin/python  
# -*- coding:utf8 -*-  

import os  
import sys
import string
import pulp as pulp
import numpy as np

def ReadFile(PathToFile):
    caseData = open(PathToFile,'r').readlines()
    coverageMatrix = []
    for line in caseData:
        str = list(line.strip().split(" "))
        digit = [int(x) for x in str]
        coverageMatrix.append(digit)
    coverageMatrix =np.array(coverageMatrix)
    data=coverageMatrix.T 
    i=0;
    B=np.zeros(data.shape[0])
    while i < data.shape[0]:
        if np.sum(data[i]) >=1 :
            B[i]=1
        i=i+1
    f=[1 for i in range(data.shape[1])]

#    prob = pulp.LpProblem("Problem", sense = "LpMinimize")
    
    variables = [pulp.LpVariable('x%d'%i , cat = pulp.LpBinary) for i in range(0, data.shape[1])]
    objective = pulp.lpSum([f[i]*variables[i] for i in range(data.shape[1])])
    constraints = []
    for i in range(0,data.shape[0]):
        constraints.append(pulp.lpSum([data[i][j]*variables[j] for j in range(0 ,data.shape[1])]) >= B[i])
        
    res=solve_ilp(objective,constraints)
    if res != None:
        print("Result:")
        for v in res:
            if v.varValue > 0:
                print('%s %g' %(v.name, v.varValue))
                list_str=list(v.name)
                list_str.pop(0)
                list_str="".join(list_str)
                i=int(list_str)+1
                file = open("result%d.txt"%(i-1))
                wflag=0
                for line in file.readlines():
                    key = "model:"
                    if key in line:
                        wflag=1
                    if wflag==1:
                        print(line)
                print("################")                
    print('Coverage percent: {:.2f}%'.format(np.sum(B)/data.shape[0]*100))



def solve_ilp(objective , constraints) : 
    print (objective)
    print (constraints)
    prob = pulp.LpProblem('LP1' , pulp.LpMinimize) 
    prob += objective 
    for cons in constraints : 
        prob += cons 
    status = prob.solve() 
    if status != 1 : 
        return None 
    else :
        return prob.variables()
       # return [v.varValue for v in prob.variables()]


def main(PathToFile):
    ReadFile(PathToFile)


if __name__=="__main__":
    if len(sys.argv) < 2 :
        print("Usage: python3 compute.py <file>")
    elif os.path.isfile(sys.argv[1]) :
        main(sys.argv[1])
    else:
        print("%s is not a file!!!"%(sys.argv[1]))


