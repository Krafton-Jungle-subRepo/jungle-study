# RBTREE의 삭제에 대한 이해

RB tree의 삭제는 doubly black을 설정하고 해결하는 방법이 굉장히 복잡하다. 따라서 doubly black가 leaf node에서 발생하게 하여 상황을 단순화하여 설명해 보고자 한다.

#
## doubly black의 4가지 상태와 변형
---

doubly black이 발생된 상황을 해결하기 위해 일반적으로 4가지 상태로 나누어 생각한다.

1. 형제 노드가 Red인 경우

2. 형제 노드가 Black이고 형제의 자식들도 모두 black인 경우

3. 형제 노드가 Black이고 형제의 자식 중 하나가 Red이고 형제의 왼쪽 자식이 Red인 경우

4. 형제 노드가 Black이이고 형제의 자식 중 하나가 Red이고 형제의 오른쪽 자식이 Red인 경우

이렇게 4가지 경우로 분류되는 경우, doubly black이 발생하는 상황은 삭제되고자 하는 값이 처음부터 leaf에 있거나, 삭제되고자 하는 값을 가진 노드가 2개의 자식을 가지고 있어 값을 successor나 predecessor와 교환 한 후 successor나 predecessor를 삭제할 때, 이 노드가 자식이 없는 leaf인 경우이다. 자식이 1개이거나 successor나 predecessor가 자식을 가지고 있는 경우 삭제되는 노드는 leaf가 아니다. 이 때, 재귀적인 방법을 사용하여 삭제되는 node를 무조건 leaf node로 만들 수 있다.

```python
def delete_node_to_leaf(delete_node):

    if delete_node is leaf:
        break
    
    else:
        successor = find_successor(delete_node)

    swap_key(delete_node, successor)
    delete_node_to_leaf(successor)
```

successor를 predecessor로 치환하여도 삭제하고자 하는 노드를 leaf 노드로 할 수 있다.

삭제하고자 하는 노드가 leaf임이 보장되면, doubly black은 최초에 무조건 nil에서만 발생하고, doubly black이 발생하는 4가지 경우를 조금 더 일반화하여 생각할 수 있다.

##
#### 1. 형제 노드가 Red인 경우
어떤 노드에서 nil까지의 black 노드 수가 같아야 한다는 규칙과 red 노드의 자식은 black이라는 규칙에 따라 형제 node는 무조건 2개의 black 노드를 가진다. 형제의 자식 노드(black)들은 0 ~ 2개의 red 자식 노드를 가진다.

> 형제 node가 red 이고 2개의 black 자식을 가지는 경우

로 바꾸어 생각할 수 있다.

##
#### 2. 형제 노드가 Black인 경우
: doubly black이 발생한 node가 부모 node의 왼쪽 자식이라 가정한다.

- 형제 노드가 1개 이상의 red 자식을 가진 경우

형제 node가 오른쪽 red 자식을 가진 경우 회전 과정에서 오른쪽 red 자식이 black이 되며 black height를 유지할 수 있다.

또한 형제가 오른쪽 red 자식 없이 왼쪽 red 자식만 가진 경우, 회전을 통해 오른쪽 red 자식을 가지게 되도록 상황을 바꿀 수 있다.

- 형제 노드가 2개의 black 자식을 가진 경우

doubly black이 발생한 노드가 nil node이므로 **형제 노드는 nil을 제외한 black 자식을 가질 수 없다**

우선 상황을 단순하게 자르기 위해 한 가지 상황으로 분류한다.

> 형제 node가 black인 경우


#
## leaf node 삭제시의 doubly black
---

##
### doubly black에 대한 생각

doubly black은 black height 규칙을 지키기 위해 특정 node에 black node가 겹쳐 있어 black height 계산 시 black node가 하나 더 있는 것처럼 생각하기 위한 개념이다. 따라서 이를 해결하기 위해 doubly black이 발생한 경로에 black node를 추가해 주어 해결이 가능하다. black node를 추가하는 방법에는 2가지 방법이 있다.

1. 해당 경로의 red node를 black으로 변경한다.

red node를 black으로 바꿀 때에는 새로운 red가 추가되지 않기 때문에 red node가 한 경로에 연속으로 2번 나올 수 없다는 규칙이 위배될 수 없다.

2. 회전을 통해 해당 경로에 black node를 추가한다.

회전을 통해 해당 경로에 black node를 가져오는 경우, 회전의 반대쪽에서 다시 black height가 위반되는 문제가 발생할 수 있다. 결국 doubly black을 해결하는 근본적인 방법은 1번이 되어야 할 것이다.

##
### 상황별 doubly black의 해결방법

위에서 정리한 것처럼 leaf node를 삭제할 때의 doubly black은 다음 2가지 경우로 구분할 수 있다.

1. 형제 node가 red이고 2개의 black 자식을 가지는 경우

2. 형제 node가 black인 경우

다음 2가지 상황에 대해 doubly black을 해결하는 방법에 대해 생각해 본다.

##
#### 1. 형제 node가 red이고 2개의 black 자식을 가지는 경우
형제 node가 red인 경우, 부모 node는 2개의 red node가 연속으로 나올 수 없다는 규칙에 의해 무조건 black이다. 따라서 부모를 doubly black이 발생한 방향으로, 형제 node가 부모가 되는 방향으로 회전 후 새로운 부모 node(이전 형제 node)의 색을 black으로 바꾸어 주면 black height가 만족된다. 이 때, 형제의 왼쪽 자식이 원래 부모 node의 오른쪽 자식이 되는데, black height를 만족하기 위해 이 node를 red로 바꿔주면 doubly black이 해결된다.

##
#### 2. 형제 node가 black인 경우
형제 node가 black인 경우엔 다음과 같은 상황으로 나눌 수 있다.

1. 형제 node가 오른쪽 red 자식을 가진 경우

왼쪽으로 회전 후 오른쪽 자식을 black으로 바꾼다. 이 때, 기존 black height를 위반하지 않기 위해 부모는 검정색으로, 형제는 원래 부모의 색으로 변경한다.

→ _이 과정을 형제와 부모의 색을 변경한다 라고 기술하는 경우가 많다._

2. 형제 node가 왼쪽 red 자식을 가진 경우

위 내용처럼 회전을 통해 형제 node가 오른쪽 red 자식을 가진 상태로 변경한다. 이후 1번과 동일한 과정으로 해결한다.

3. 형제 node가 자식이 없는 경우

이 부분이 가장 까다롭다. 결국 근본적으로 doubly black을 해결하기 위해서는 red node를 black node로 바꿔주는 과정이 필요한데, 이 경우에는 black으로 바꾸어줄 red node가 없다. 따라서 조부모 node나 부모의 형제 node를 활용해 상황을 해결해야 한다.

우선, 이 상황을 해결하기 위해 형제 node를 red로 변경한 후, 부모 node에 extra black을 부여한다.

- extra black: node에 추가적인 black height를 부여, black node에 extra black이 부여된 상황을 doubly black이라 한다.

→ _이 과정을 doubly black을 모아 부모에게 전파한다 라고 기술하는 경우가 많다._

##
### extra black의 해결

부모 node에 extra black이 부여된 상황은 다음 3가지 상황으로 나눌 수 있다.

1. 부모 node가 root node인 경우

2. 부모 node가 red node인 경우

3. 부모 node가 black node인 경우

1, 2번 상황은 간단하게 해결할 수 있다.

#### 1. 부모 node가 root node인 경우
root node를 통과하여 계산하는 모든 경우에 대해 doubly black이 적용되므로, 부여된 extra black을 삭제해도 black height 규칙을 위반하지 않는다.

→ extra black을 삭제한다.

#### 2. 부모 node가 red node인 경우
red node에 부여된 경우, red node를 black node로 변경하고 extra black을 삭제하면 black height 규칙을 위반하지 않는다.

→ extra black이 부여된 red 부모 node의 색상을 black으로 변경한다.

#### 3. 부모 node가 black node인 경우
이 경우, leaf node가 아닌 내부 node에서 새로운 doubly black이 발생한다. 따라서 내부 node의 doubly black을 해결하기 위한 새로운 방법이 필요하다.

##
### 내부 node에서 발생한 doubly black

내부 node에서 doubly black을 해결할 때 고려해야 하는 가장 중요한 것은, doubly black이 발생한 node가 root node가 아닌 이상 root node에서 시작한 모든 경로에 대해 black height가 유지되어야 한다는 것이다. 마찬가지로 근본적으로 이를 해결하기 위해서 red node의 색상을 black node로 변경하거나 doubly black이 발생한 node가 부모 노드여야 한다.

내부 node에서 doubly black이 발생한 경우, doubly black 노드의 parent에서 계산한 모든 경로의 black height가 같아야 하므로 doubly black의 형제 node는 무조건 leaf까지의 경로에 black node를 가지는 2개의 자식을 가져야 한다.

1. 형제 node가 red인 경우

부모 node의 색을 red, 형제 node의 색을 black으로 바꾼 후 형제 node가 parent가 되도록 회전하여 해결한다.

2. 형제 node가 black인 경우

leaf node에서와 똑같은 방법으로 해결한다.