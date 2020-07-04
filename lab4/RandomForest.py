#!/usr/bin/env python
# coding: utf-8
# author = 0712238, Yan-Tong Lin

import numpy  as np
import pandas as pd
import random
from collections import defaultdict


# # Hyper Params and other

fname = "./dat/iris.data"
TEST = True
n_feature = 64
n_class = 10
LAB = n_feature 
epsilon = 0.00000001

# # preprocessing

def load_data(fname, partition=(8,1,1)):
    # read in, df to nparray
    df = pd.read_csv(fname, header=None)
    npd = np.array(df)
    n = npd.shape[0]
    
    # tag to id, id to tag, transform
    tag_map = defaultdict(int)
    tag_to_id = defaultdict(int)
    id_to_tag = defaultdict(int)
    for d in npd:
        tag_map[d[LAB]] += 1
    
    cnt = 0
    for k, v in tag_map.items():
        id_to_tag[cnt] = k
        tag_to_id[k] = cnt
        cnt += 1
        
    for i in range(n):
        npd[i][LAB] = tag_to_id[npd[i][LAB]]
    #print(tag_to_id)
    #print(id_to_tag)
    
    # shuffle(no when testing)
    np.random.shuffle(npd)
    if not TEST:
        np.random.shuffle(npd)
    
    # partition
    cut1 = int(n*partition[0]/sum(partition))
    cut2 = int((n*(partition[0] + partition[1])/sum(partition)))
    # print(cut1, cut2)
    train_set = npd[:cut1, :]
    valid_set = npd[cut1:cut2, :]
    test_set = npd[cut2:, :]
    
    return train_set, valid_set, test_set, tag_to_id, id_to_tag


def Gini(data, feature_id = -1, threshold = None):
    n = len(data)
    sigma = 0.0
    # first dimension, lc or rc
    # second dimension, map label type to cnt, map[n_class] = total
    group_labels = [defaultdict(int), defaultdict(int)] # group 1 stat, group 2 stat
    for d in data:
        if feature_id == -1:
            group_labels[0][d[LAB]] += 1
            group_labels[0][n_class] += 1
        else:
            group_labels[d[feature_id] < threshold][d[LAB]] += 1
            group_labels[d[feature_id] < threshold][n_class] += 1 #total
    #print(group_labels)
    for g in group_labels:
        w = g[n_class]/n
        cur = 0.0
        if(g[n_class] == 0):
            continue
        for i in range(n_class):
            p = g[i]/g[n_class]
            cur += p*p
        sigma += w*cur
    return 1 - sigma
    

class Node(): # subtree
    def __init__(self):
        self.c = [None, None] # child, c[0] => < threshold , c[1]
        self.sf = None # split feature
        self.th = None # threshold
        self.maj = None # majority label in this subtree
        self.depth = None #depth
        self.leaf = True
    
    def split(self, data, criterion="gini", max_features=None, max_depth=None, min_impurity_decrease=None, depth=0): 
        n = len(data)
        self.depth = depth
        
        # deal with min_impurity_decrease
        if min_impurity_decrease == None:
            min_impurity_decrease = epsilon # inf small to represent any gain > epsilon is ok
        
        # criterion => func
        if criterion == "gini":
            func = Gini
        elif criterion == "entropy":
            func = None
        else:
            print("not a valid critirien, use Gini's impurity")
            func = Gini
        
        # calc majority
        vote = defaultdict(int)
        for d in data:
            vote[d[LAB]] += 1
        self.maj = max(vote, key=vote.get)
        
        # cut if maxd exceed
        if(max_depth and self.depth >= max_depth):
            print("maxd_cut")
            self.leaf = True
            return
        
        # feature_mask (max_feature)
        mask = np.zeros(n_feature)
        if max_features == None :
            n_sample_f = n_feature
        elif max_features == "sqrt":
            n_sample_f = int(np.ceil(np.sqrt(n_feature)))
        elif max_features == "log":
            n_sample_f = int(np.ceil(np.log2(n_feature)))
        elif max_features == "one":
            n_sample_f = 1
        else:
            print("Error: No Such Max Feature")
            assert(False)
        
        # random.choices may with repeat
        # random.sample without
        sampled_features = random.sample(list(range(n_feature)), k=n_sample_f)
        for sampled_feature in sampled_features:
            mask[sampled_feature] = 1
            
        # select feature 
        best_gain = 0.0
        best_branch = (None, None)
        cur_func = func(data)
        # cut if impurity is low enough
        if(cur_func < min_impurity_decrease):
            # print("min_impuraity cut"), left element
            self.leaf = True
            return 
        
        for f in range(n_feature):
            if(not mask[f]):
                continue
            #print(data.shape)
            sort_by_f = data[data[:,f].argsort()]
            for i in range(n-1):
                th = (sort_by_f[i+1][f] + sort_by_f[i][f])/2
                #print(th)
                cur_gain = abs(func(sort_by_f, f, th) - cur_func)
                if(cur_gain > best_gain):
                    best_branch = (f, th)
                    best_gain = cur_gain
        
        # cut if not enough gain
        if(best_gain < min_impurity_decrease):
            print("min_impuraity_gain cut")
            self.leaf = True
            return 
        else:
            self.leaf = False
        
        # actually split by best
        self.sf = best_branch[0]
        self.th = best_branch[1]
        
        c_data = [[], []]
        for d in data:
            c_data[d[best_branch[0]] < best_branch[1]].append(d)
        # print(c_data)
        self.c = [None, None]
        for i in range(2):
            self.c[i] = Node()
            self.c[i].split(np.array(c_data[i]), criterion, max_features, max_depth, min_impurity_decrease, depth+1)
        return


class CART:
    def __init__(self):
        self.rt = Node()
    def train(self, dataset, criterion="gini", max_features=None, max_depth=None, min_impurity_decrease=None):
        self.rt.split(dataset, criterion, max_features, max_depth, min_impurity_decrease)
    def predict(self, v):
        cur = self.rt
        while(cur.leaf == False):
            cur = cur.c[v[cur.sf] < cur.th]
        return cur.maj
    def calc_ac(self, testd):
        total = 0.0
        succ = 0.0
        for d in testd:
            succ += int(self.predict(d) == d[LAB])
            total += 1
        return succ/total

class RandomForest:
    def __init__(self, n_estimators=100, criterion="gini", max_features="sqrt", max_depth=None, min_impurity_decrease=None, bootstrap=True, max_samples=None):
        self.n_estimators = n_estimators
        self.criterion = criterion
        self.max_features = max_features
        self.max_depth = max_depth
        self.min_impurity_decrease = min_impurity_decrease
        self.max_samples = max_samples
        self.dtrees = []
        self.bootstrap = bootstrap
        
    def train(self, data):
        n = data.shape[0]
        if self.max_samples == None:
            n_population = n
        elif type(self.max_samples) == float:
            n_population = int(n*self.max_samples)
        elif type(self.max_samples) == int:
            self.n_polulation = self.max_samples
        else:
            print("MAX SAMPLE TYPE ERROR")
            assert(False)
            return
        
        for i in range(self.n_estimators):
            ti = CART()
            if self.bootstrap == True:
                sampled_ids = np.random.choice(n, n_population, replace=True)
            else:
                sampled_ids = list(range(n))
            bootstrap_data = data[sampled_ids]
            ti.train(bootstrap_data, criterion=self.criterion, max_features=self.max_features, max_depth=self.max_depth, min_impurity_decrease=self.min_impurity_decrease)
            self.dtrees.append(ti)
        return
            
    def predict(self, v):
        cnt = np.zeros(n_class)
        for i in range(self.n_estimators):
            cnt[self.dtrees[i].predict(v)] += 1
        return np.argmax(cnt)
    
    def calc_ac(self, testd):
        total = 0.0
        succ = 0.0
        for d in testd:
            succ += int(self.predict(d) == d[LAB])
            total += 1
        return succ/total  