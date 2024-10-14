# RB-Tree
---

#
## Binary Search Tree와 RB-Tree
---

RB-Tree는 다음의 규칙들을 만족한다.

1. 모든 node는 black 또는 red의 색을 가진다

2. root node는 항상 black이다

3. NIL node는 항상 black이다.

4. red node는 연속해서 나타날 수 없다. (red property)

5. 임의의 node에서 leaf node까지의 모든 경로에 대하여 한 경로상 black node의 개수(black height)는 같다. (black property)

4, 5번 규칙에 의하여, root node에서 leaf node까지의 경로 중 최소 경로는 black node로만 이루어진 경로이며 이 때의 거리를 p라고 하면, root node에서 leaf node까지의 경로 중 최대 경로는 black node 사이사이에 red node가 들어간 p $\times$ 2 - 1의 거리를 가진다. 따라서 RB-Tree는 검색에 최대 $2log_{2}N$의 시간이 소요되는 유사 균형 BST가 된다.

##
## RB-Tree의 삽입
---

RB-Tree의 삽입은 항상 leaf node에서 이루어지며, 새로 삽입되는 node는 red 색상을 부여하여 삽입 직후 black property 규칙이 위반되지 않음을 보장한다.

이 때, 추가되는 node의 parent가 red node일 경우 red property가 위반될 수 있다. 따라서 새로운 node 삽입시 red property 위반 여부를 확인한 후, 위반시 조정이 필요하다.

##
### red property 위반 시 조정

red property가 위반되었을 때의 해결책은 연속된 red node 중 하나의 색상을 black으로 변경하거나(black property가 위반되지 않도록) red node를 red property가 위반되지 않는 곳으로 이동시킨다. 두 가지 방식을 상황에 맞게 적용하여 RB-Tree를 조정한다.

##
#### red node를 black node로 변경하는 경우

red node를 black node로 변경하는 경우, 색이 변경된 node가 포함된 경로의 black height가 1이 증가한다. 이를 해결하기 위해 삽입된 node의 parent node(연결된 red node의 parent node)의 색을 black으로 변경하고, parent node의 parent node(삽입된 node의 grand parent)의 색을 red로 변경한다. 이 때, 노드를 삽입하기 전 RB-Tree는 red property를 만족하고 있었으므로, grand parent node의 색은 무조건 검정색이다.

이 경우, 삽입 node에 대한 red property가 해결되었으며, grand parent node를 기준으로 노드가 삽입된 쪽 경로의 black property는 만족되었다. 하지만 이 경우 2가지 문제가 발생할 수 있다.

1. grand parent node의 반대편 경로 (uncle node 방향)의 black height가 1 감소하여 black property 위반

2. grand parent node의 parent가 red node일 경우 새로운 red property 위반 발생

1번 문제에서, uncle node가 red node일 경우, uncle node의 색을 black으로 변경하여 해결할 수 있다. uncle node가 black node일 경우, uncle node의 각 child에 대해 black을 추가하여 해결할 수도 있으나, 삽입 node의 grand parent에서 red parent 방향 경로의 black height가 1이므로 uncle node는 0 ~ 2개의 red child만을 가질 수 있다. 2개의 red child를 가질 경우 두 red child의 색을 black으로 변경하여 해결할 수 있으나, 이는 일반화하기 어렵다. 따라서 1번 문제에서 다음의 규칙을 도출해 낼 수 있다.

> red property가 위반되었을 때, uncle node가 red일 경우 red parent node와 uncle node의 색을 black, grand parent node의 색을 red로 바꾸어 red property 위반을 해결한다.

2번 문제에서, grand parent node가 black에서 red로 바뀌었으므로 grand parent node의 parent의 색을 확인하여 새로운 red property 위반이 발생하는지 확인할 필요가 있다. 만약 새로운 red property 발생시 grand parent node에 대하여 재귀적으로 red property 위반 조정을 실시한다.

##
#### red node를 red property가 위반되지 않는 곳으로 옮기는 경우

RB-Tree는 BST의 속성을 유지해야 하므로 red node를 다른 위치로 단순히 옮기기는 쉽지 않다. 이 경우, BST의 속성을 유지하면서 node의 위치를 옮기기 위해 rotation을 사용한다.

- BST의 rotation

BST내 임의의 node t에 대하여 rotation을 수행하는 경우 BST의 속성이 위반되지 않음을 확인해야 한다. 만약, node t를 root로 하는 임의의 sub BST에 대하여 right rotation을 수행하는 경우, t→left가 새로운 root가 되고, t는 t→left의 right child가 된다. 또한 t→left의 right child는 t의 left child가 된다. 이 경우, t→left < t, t→left→right < t임이 보장되므로 left rotation 수행 시 BST의 속성이 위반되지 않는다. left와 right를 바꾸어도 성립한다.

- red property 위반과 rotation

앞에서 red property 위반시 red child node의 grand parent는 항상 black임을 확인했다. 이 때, red parent node를 black으로, grand parent node를 red로 바꾼 후, red parent가 grand parent의 자리로 가도록 회전한다면 black property를 위반하지 않으면서 red property를 해결할 수 있다.

하지만 만약 grand parent의 left child가 red parent이고, red parent의 right child가 red child일 경우, 회전시 red child가 red로 변경된 grand parent node의 left child가 되므로 새로운 red property가 발생한다. 이를 예방하기 위해 red child가 red parent 위치로, red parent가 red parent의 left child 위치로 이동하도록 먼저 회전할 필요가 있다. 마찬가지로 left와 right를 바꾸어도 성립한다.

> red child, red parent, black grand parent가 한 줄로 정렬되도록 회전한 후, red parent를 black으로, grand parent를 red로 변경한 후 parent가 grand parent 자리로 이동하도록 회전한다.

##
## RB-Tree의 삭제
---

RB-Tree의 삭제 시 BST와 동일하게 삭제하고자 하는 key를 가진 node의 predecessor나 successor와 값을 변경 후 삭제한다. 만약 삭제하는 predecessor나 successor가 black일 경우, 해당 node를 경유하는 경로의 black height가 1 줄어들어 black property가 위반된다. 이를 해결하기 위해 extra black의 개념을 사용한다.

##
### black property 위반과 extra black

RB-Tree에서 삭제하고자 하는 key 값을 가진 node p에 대하여, 삭제되는 node는 node p와 key값을 바꾼 p의 predecessor나 successor이다. 삭제되는 node의 자리는 predecessor인 경우 left child, successor의 경우 right child가 대체한다. 만약 left child나 successor가 NIL node인 경우에도 성립한다. 이 때, 대체되는 node에 extra black을 부여하여 black height를 1 증가시켜 임시로 black property를 해결한다.

만약, extra black이 red node에 부여되었을 경우, 그 node를 black으로 바꾼다면 red property와 black property가 모두 만족되어 extra black 상황이 해결된다. 그러나 extra black이 black node에 부여된 경우에는 이러한 방법으로 해결할 수 없으며, 이 상황을 doubly black이라 한다.

##
### doubly black의 해결

doubly black의 해결의 근본적인 해결을 위해서 해당 경로의 black height가 1 증가해야 한다. 하지만 새로운 black node를 추가할 수 없으므로 red node를 black node로 전환하거나, 회전을 통해 해당 경로에 새로운 black node를 추가하여 해결해야 한다.

만약 삭제되는 node가 predecessor라 가정하면 predecessor의 right child는 NIL이다. 이 때, 삭제 전 predecessor를 기준으로 right child쪽 경로의 black height가 1이므로 predecessor는 left child로 NIL 또는 leaf node인 red node일 수밖에 없다. 따라서 doubly black이 발생하는 경우는 predecessor가 삭제되는 경우 left child가 NIL인 경우 발생한다. 마찬가지로 successor가 삭제되는 경우 successor의 right child가 NIL인 경우 발생한다.

삭제 전 predecessor에서 출발하는 leaf까지 경로의 black height가 1이므로, predecessor의 sibling node의 black height 역시 1이다. 따라서 doubly black이 발생한 경우를 다음 2가지 상황으로 나누어 생각할 수 있다.

1. sibling node가 red이고 2개의 black child를 가지는 경우 → 이 경우 red property에 의해 parent node가 black임이 보장된다.

2. sibling node가 black이고 0 ~ 2개의 red child를 가지는 경우

각 상황별로 어떻게 doubly black을 해결해야 할 지 생각해보자.

##
#### 1. sibling node가 red인 경우

sibling node가 red인 경우 parent node는 black임을 앞에서 확인하였고, 따라서 parent node의 black height는 2이며 sibling node는 2개의 black child를 가진다. 이 상황에서 sibling node의 색을 black으로 바꾼 후 sibling node가 parent node의 자리로 가도록 회전한다면 새로운 parent node 기준으로 doubly black이 발생한 반대 방향의 black height는 유지되며, doubly black은 sibling node가 black인 상황으로 변경된다. 이 상황에서 sibling node가 black인 상황을 해결하면 doubly black을 해결할 수 있다.

##
#### 2. sibling node가 black인 경우

설명을 위해 doubly black이 발생한 node가 parent node의 left child, sibling node가 parent node의 right child라 가정하자. 이 상황을 다음 4가지 경우로 나눌 수 있다.

1. sibling node가 red right child만을 가지는 경우

2. sibling node가 red left child만을 가지는 경우

3. sibling node가 2개의 red child를 가지는 경우

4. sibling node의 양쪽 child가 모두 NIL인 경우

앞서 확인했던 것처럼 parent node의 black height는 parent node가 black인 경우 2, red인 경우 1이다. 이 사실을 기억하고 위의 4가지 경우에 대해 doubly black을 해결해보자.

1. sibling node가 red right child만을 가지는 경우

이 상황에서 sibling node가 parent 자리에 오도록 회전한다 생각해보자. 기존 parent node가 sibling node의 left child가 될 것이다. 만약 parent node가 red라면 새로운 parent node 기준 doubly black쪽 경로의 black height가 1이 되어 doubly black이 해결되고, 반대쪽 경로 역시 black height가 1이 유지된다.

만약 parent node가 black이라면 doubly black쪽 경로의 black height는 2로 doubly black이 해결되지만 반대쪽 경로의 black height는 1이 되어 black property 위반이 발생한다. 이 경우, 기존 sibling node의 right child를 black으로 바꾸어 주면 black property와 red property 위반 없이 상황을 해결할 수 있다.

sibling node가 왼쪽 red child도 가지고 있는 3번 상황을 이와 같은 방식으로 해결한다 생각해보면, 기존 sibling node의 left child가 기존 parent node의 right child가 되는데, 이 때 기존 parent node는 black이기 때문에 red property 위반이 발생하지 않음을 확인할 수 있다. 따라서 3번 경우도 1번 경우와 똑같이 해결할 수 있다.

2. sibling node가 red left child만을 가지는 경우

이 상황에서 sibling node를 red, sibling node의 red left child를 black으로 바꾸어 준 후 red left child가 sibling node의 위치로 가도록 회전한다면 1번 상황이 됨을 알 수 있다. 이후 1번 상황과 똑같이 해결한다.

4. sibling node의 양쪽 child가 모두 NIL인 경우 (양쪽 child가 모두 black인 경우)

이 경우, parent node의 색에 따라 parent node의 black height가 1 또는 2가 된다. 이 때, sibling node의 색을 red로 변경하고 parent node에 extra black을 부여한다면 parent node의 left, right 경로 모두 black height가 유지됨을 알 수 있다. 또한 sibling node의 자녀는 모두 NIL(black) node 이므로 red property가 위반되지 않는다. 만약 parent node가 red일 경우 parent node를 black으로 바꾸어 주면 상황이 해결된다. 만약 parnet node가 black일 경우, parent node를 기준으로 새로운 doubly black이 발생한다. 이 때는 앞선 과정들을 재귀적으로 반복하여 해결할 수 있다.


오타, 잘못된 내용 지적, 질문 환영합니다 :)