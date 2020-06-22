---

title: Introduction to Artificial Intelligence
tags: 2020, AI, NCTU, lecturenote
author : Maxwill lin, Yan-Tong Lin
description :  Introduction to Artificial Intelligence

---

# Introduction to Artificial Intelligence, 2020 spring

[TOC]

## Contact Information
- author
    - Yan-Tong Lin
- email
    - 0312fs3@gmail.com
- online version of this note
    - https://hackmd.io/d1sg-yhiTSiNcxgy8ziBvQ

## Labs
- [Intro to AI lab1](/4Ip9qmmkRcu0d3aJVGP1Kw)
- lab2 on github
- [Intro to AI Written Assignment #1](/PjbPwQsETb2OQXuKBArpFg)
- [Intro to AI lab3](/XYvYo1w2TgCUG7gcqlKBrA)

---

## The course turned online
- [AI 2020 before online](/XHG8_WAfRuCahj-jkrvJvg)

---

# Final Exam Prepare, Week 18?(6/21)

---

## Set 1 - Introduction

---

## Set 2 - Search

### frontier and explore set

### searches (mem / time / best?)

### A* - consistent <= admissible 
- consistent
    - triangular ineq
- admissible
    - no overestimate
- Note: A technique
    - max(h1, h2) is still admissible

---

## Set 3 - CSP

### Task decription 
- Variable
- Domain
- Constraints

### DCSP, representation as (hyper) graph
![](https://i.imgur.com/BhnGoXZ.png)


### Consistency
- node 
    - unary constraint satisfied
- arc
    - for "an" "arc" Xi -> Xj
    - domain of Xi has valid assignment of Xj
        - i.e. Xi -> non empty set
        - according to edge(Xi,Xj)
- path
    - for a path Xi => Xm => Xj
    - valid assignment of Xm exist for every assignment of Xi, Xj
        - according to edge(Xi,Xm), edge(Xm,Xj)

### AC3
- idea: maintain arc-consistency by reducing domain size
- Init: S, a set of "arc"s
- for each time
    - pick an arc from S
    - make it arc-consistent by reducing domain
    - if domain of Xi changes => add arcs of (?->Xi) to set
- until D (or S) is empty

![](https://i.imgur.com/8qJvFKo.png =50%x)

### Backtracking

#### Heuristics!
- Which Var
    - MRV(min remainning values)
    - Degree
- Assign What
    - LCV(least constraining value)
- usually
    - MRV => Degree => LCV

#### Interleaving Searching and Inference
- forward checking 
    - key: check if there is empty domain after assignment!
- maintaining consistenct
    - ex: run AC3 after each assignment in search

### Min-Conflicts Local Search
- Start from a complete configuration (each variable assigned by randomly selecting a value from its domain).
- Iteratively select a variable (randomly), and reassign its value to minimize conflicts.
- can solve million-queen problems!

---

## Set 4 - Adversarial Search

### Definition 
- State, Action, Player
- Transition, Terminate Function
- Utility(terminal state, player)
    - zero sum
        - sum of utilities of all players is constant 

### Part 1 - Min-Max Search
- perfect information
- deterministic
- zero sum

#### Alpha-Beta Prunning
![](https://i.imgur.com/KCc27KO.png =50%x)


### Reality => Combine with Eval Function
- estimate of winrate when cannot search further

#### Quiescent search to solve critical nxt step

### Imporvementa of Min-MAx
- singular
    - good enough => cut
- forward prun
    - similar to beam search, follow fewer paths
- transition table
    - similar to dp
![](https://i.imgur.com/BUg1LG5.png =50%x)

### Precalulated Look up table for end game
- save min-max result for end games

### Part 2 - Other Game

### solution to randomness - chance node
- Stochastic Game

### solution to imperfect info.
- can refer to my Theory of Computer Game report about 
- not in slide of Intro 2 AI

### Part 3 - past SOTA, deep blue
- enumeration and hand craft feature, even hardware

### Part 4 - MCTS
- sample the tree
- best first search idea

### The algorithm

#### UCB-1 scoring
- exploration and exploitation

#### Alpha GO and Alpha Zero

---

## Set 5 - Logical Agent !!

### Part 1 - logic

### Definition of KB/inference is quite unclear(in the note)

### Definie Logic
- Syntax
    - is the sentece "well-formed"
    - ex: =xy4+ may not be a well-fromed sentence in some rules
- Sematics
    - what a sentence means
    - ex: x+y = 4 
- Model
    - a possible way the world is 
    - ex: x = 1, y = 2
- Validaity of model M under sentence $s$
    - M is a model of s
    - M statisfies s
- $M(s)$ - the set of all models of $s$

### Entailment
- $a \models b$
- i.e. $M(a) \subseteq M(b)$ 

### Inference , Sound and Complete
- Inference is the process of deriving a new sentence from a set of known sentences
- $KB \vdash_i \alpha$
    - $\alpha$ can be inferenced from $KB$ with algorithm $i$
- A inference algorith $i$ is 
    - Sound if
        - $KB \vdash_i \alpha \implies KB \models \alpha$
    - Complete if
        - $KB \vdash_i \alpha \Longleftarrow KB \models \alpha$



### Propositional Logic
- Syntax
    - by CFG
- Sementic
    - by Truth Table


----

### Part 2 - How to solve (if a is true)

### Enumeration of models O(2^N)

### Search
- using inference rules
- using logic equivalence

### Validity and Satisfiability, relation to inference
- define for sentence s
- valid
    - $M(s) = U$
    - proof by deduction
        - $a \models b$ iff $a\implies b$ is valid
- satisfiable
    - $M(s) \neq \emptyset$
    - proof by contradiction
            - $a \models b$ iff $a \neg b$ is unsatisfiable


### Resolution Rule for Propositional Logic
![](https://i.imgur.com/EJyTIre.png =70%x)

### CNF for resolution
- Conjunctive Normal Form(CNF)
    - and of clauses
- clause
    -  or of literals
- literal 
    -  atom or neg atom
-  conversion
    -  eliminations + De Morgan's

### Resolution algorithm for CNF
- to proof $\alpha$
- proof $KB \wedge \neg\alpha$ is unsatisfiable
- repetative use resolution rule
    - combine clause pairs with complementary literal to make new clauses
- if lead to empty clause
    - $KB \models \alpha$
- after expand all, no empty clause
    - $KB \not\models \alpha$

#### An example
![](https://i.imgur.com/833uEzy.png =70%x)

### Horn Clauses - A speed up
- Goal clause
    - 0 positive literal
- Definite clause
    - 1 positive literal
    - is actually some implication
        - $\neg \alpha \vee \neg \beta \vee \gamma$
        - $\alpha \wedge \beta \implies \gamma$
- Horn clause
    - 0/1 
- horn property is closed under resolution 
- can use FC/BC(chaining) to spped up


### Forward Chaining (FC)
- idea
    - maintain a set of gound truths
    - if a literal $\alpha$ is true, decrement requisition number of a goal literal $\gamma$ if $\alpha$ is in premise of $\gamma$
        - $\alpha \wedge ... \implies \gamma$
![](https://i.imgur.com/J8V78In.png =70%x)
![](https://i.imgur.com/39IGiy7.png =70%x)

### Backward Chaining (BC)
- similar to FC, but go from target
- from prove $\alpha$ to prove all premise for some implication to $\alpha$

----

### Part 3 - FOL, more than proposition

### Representations
- Constant($C$)
    - Nouns, Values ...
- Predicate($P$)
    - $C^N \to \{True,False\}$
- Function($F$)
    - $C \to C$

### Model
- Domain
    - non empty set of constants
- Relations
    - A relation is defined by the set of all the "tuple"s of objects that are related
    - can be unary, binary, ...
    - can be use as definition of a predicate
        - if the tuple is in the relation set
- Funtion Relation
    - $C \to C$
- Interpretation of Model
    - links the symbols with the actual objects and relations in the model.
    - referent
        - the actual object being referred to
        - Classmate(John,Mary) is false if John refers to John the student and Mary refers to John's cat.

### An example graph of Model on textbook
![](https://i.imgur.com/baBiC74.png =60%x)


### Syntax
![](https://i.imgur.com/hZkcRCN.png =60%x)

### Existial/Universal Q and Duality(De Morgan's in FOL)
- trivial

### Equivalence
- for all model!

### Definitions, Axioms, Theorems
- Definition 
    - add new predicate from existing ones
    - to enrich representation
- Axioms
    - sentences in KB that are not entailed by others
    - include definitions
- Theorem
    - useful sentence that implied by others

### Assertion and Queries for FOL KB
- assertion
    - add to KB
- query
    - ask KB
    - ask True/False (Ask)
    - ask domain of True (AskVars)
- substitution(bindding list)
    - notation $\{var/instance\}$

----

### Part 4: Inference for FOL

### Difference with Propositional Logic
- Variable
- Quantifier

### Universal Instantiation
- transform to symbol without variable
![](https://i.imgur.com/Zx3BfZb.png =50%x)
- Note: infinite if have function
    - consider F...(F(x)) as ground term

### Existential Instantiation
- Skolem constant
    - means find a arbitrary instance?
![](https://i.imgur.com/n74Y0zC.png =70%x)


###  Propositionalization
- idea: try to reduce to propositional case
    - generate all, but may not be possible to do all!
    - solution; iteratively increment
- Herbrand's theorem (1930)
    - If a sentence is entailed by an FOL KB, it is entailed by a finite subset of the propositional KB
- Inference in FOL via propositionalization is complete
    - all entailed sentences can be found
- Entailment in FOL is semidecidable
    - if the KB contains functions
    - non-entailment can not be proved.

### Unification for reducing irrelavence
![](https://i.imgur.com/3pFSNyI.png =70%x)

### Genralized Modus Ponens
![](https://i.imgur.com/iweaGmI.png =70%x)

### FC for FOL
![](https://i.imgur.com/W25w56s.png =70%x)
![](https://i.imgur.com/ZU8Qokg.png =70%x)


### BC for FOL
- dfs 
- OR, AND - node
![](https://i.imgur.com/SV8jniP.png =70%x)


### Resolution for FOL
![](https://i.imgur.com/mm0InCo.png =70%x)

### Convertion to CNF
![](https://i.imgur.com/5LLUz4g.png =70%x)
![](https://i.imgur.com/u3SwOcW.png =70%x)
- Skolemize, use function instead of variable to do EI

### Solve the example by resolution
- my obs: range down premise by combination
![](https://i.imgur.com/zHjMs83.png =70%x)

### Next?
- SOL(second order logic)
    - quantify over predicate
    - predicate that take predicate as argument
- automated theorem proving 
    - FOL based
    - human interact with it
    - have found some proofs!

---

## Set 6 - Learning from data, Supervised Methods

### SL / UL / RL

### Decision Tree - An example
- Shannon's Entropy
    - $-\sum P log P$
- Ginni's Impurity
    - $1 - \sum P^2$
- Choose Attribute with mast $\Delta H$
    - information gain
    - H(now) - weighted sum of H(child)
    - $\Delta H = H(u) - \sum_i^{m} \frac{N_i}{N}H(v_i)$


### A nice graph for SL
![](https://i.imgur.com/b6654UJ.png =70%x)


### Target / Noise(!!)
- Sample Value = Sinal + Noise

### Variance / Bias
- Variance is caused by noise
- Bias is caused by insufficient compacity of model

### Overfit / Underfit
- dilemma

### What to do
- increase sample number
- validate model complexity
    - Ockham's Razor
    - CV
    - prunning

### Amount of Data
![](https://i.imgur.com/OyXE1mj.png =70%x)

### Validation of model 
![](https://i.imgur.com/Z4YcVK5.png =70%x)


#### Cross Validation
- LOO (leave one out)

### Regularization
- adding constraint on parameter

### Consensus Based Methods
- models tends to agree on signal instead of bias!
-  Common ways to create the ensemble of different models:
    - Random subset of attributes
    - Random subset of training sample

### CART - A concrete sample of D-tree
![](https://i.imgur.com/PZbymeH.png =70%x)


### Random Forest
- bagging = bootstrap + aggregating
    - sample with replacement
- tree bagging
    - bag data
    - every tree see subset of data
- feature bagging
    - bag feature
    - every node see subset of feature
        - often use $\sqrt{|feature|}$
- trees vote for prediction
    - avg for reg, vote for classification
- no overfitting with # of tree


---

## Set 7 - Reinforcement Learning

### Definitions
- Policy, Reward, Utility

### Bellman's Eq
![](https://i.imgur.com/KcjxK6U.png =50%x)

### Passive / Active learning
- passive
    - policy is fixed
    - learn utility and model by trajectories
- active
    - learn policy
    - find by experiments

### Q-learning
- target
    - learn Q(s,a)
- without transition is OK
- formula
![](https://i.imgur.com/kl6wIL7.png =50%x)


### a numeric example 
![](https://i.imgur.com/CdYOFoA.png =70%x)

### how to choose action when learning
- Q-learning is online
- choose action by 
    - $\epsilon$-greedy

#### a opitional improvement
- discount factor
    - smaller at begin
        - to prevent propagation of noise
    - larger
        - to see the future

### function approximation
- DQN
- loss - dis(one step look ahead, current estimation of Q)

### TD learning
- idea
    - nxt state sees better
- $V(s) = V(s) + \alpha [r + \gamma V(s') - V(s)]$
- TD target
    - $r + \gamma V(s')$
- TD error
    - $r + \gamma V(s') - V(s)$

### My note
- TD method is a general concept
- SARSA, Q-learning, TD learning are its applications 

---

## Set 8 - Unsupervised Learning

### Definition
- Define the target and loss yourself!
![](https://i.imgur.com/f5yiUkd.png =70%x)


### Clustering

#### Proximity Measure
- define your self depending on tasks

#### (Point) Representation of a cluster
- use mean of mediod to repr. the whole cluster
![](https://i.imgur.com/5oB3mQp.png =70%x)

### K-means - instance of competitive learning
- competitive learning
    - data fight for right of representation!
- k is hyperparam
- I am familiar with algo, no decription here

### Hierachy Clustering
- common for "relational data"
    - the only info. used is relations of data
        - not vectorization
        - graph(or matrix) of relations instead
    - ex: biological catogory, document, music, network
- Algorithms
    - Agglomerative
        - init as many
        - merge each step
    - Divisive
        - init as one
        - devide each step

### Vector Quantization
![](https://i.imgur.com/YStuHJW.png =70%x)

#### My repr.
- initial:  a set of vectors
- step: choose a vector, move it to nearest by lr
- end: convergence to k vectors


### Self Organizing Maps(SOM)
- not in range of exam but seems interesting
- inspired by locality of human brain

### Trainning of SOM
![](https://i.imgur.com/inmqGfh.png =70%x)
![](https://i.imgur.com/PJxv4aA.png =70%x)
![](https://i.imgur.com/zp3GHln.jpg =70%x)


### My repr.
- a neuron in SOM is a point in feature space
- reponse to similar point in feature space
    - i.e. dot product bigger

### Apps of SOM
The features of SOM include: approximation of input spaces, topologically ordering, density matching and feature selection (Haykin, 1999).
- A reduced-dimension representation of the original data
- density matching
- approximate topology(proximity)
- can visualize high dimensional data


---

## Set 9 - Deep Learning

### Inspiration - Biological view
- nueron in brain!

### Weighted Sums + Non linearity
- my though: may be can choose non-linearity for each neuron
    - problem optimization hard(2^n choice)

### Error Coreection Learning / Increment Optimization
from Perceptron Algorithm to Backpropagation

### Capacity of model - XOR

### Capacity of model - the Universal Approx theorem
- my addition

### lr, momentum, early stopping

### NN as feature extractor, so go deep!

### CNN and weight sharing

---

## My note
- self supervised learning + finetuning is getting important
    - ex: BERT, GTP(LM)
- ~6/20 started this note
- 6/21 17:42 finish this note

---