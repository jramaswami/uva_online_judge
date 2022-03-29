// UVA ::
// <URL>
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Node {
    int leftValue;
    int leftFreq;
    int maxFreq;
    int rightValue;
    int rightFreq;
};

const Node NONE{0, 0, INT_MIN, 0, 0};

ostream& operator<<(ostream &os, const Node &node) {
    os << "Node(" << node.leftValue << ", " << node.leftFreq << ", " << node.maxFreq
       << ", " << node.rightValue << ", " << node.rightFreq << ")";
    return os;
}

Node operator+ (const Node &leftNode, const Node &rightNode) {
    if (leftNode.maxFreq == INT_MIN) {
        return Node{rightNode.leftValue, rightNode.leftFreq, rightNode.maxFreq, rightNode.rightValue, rightNode.rightFreq};
    }
    if (rightNode.maxFreq == INT_MIN) {
        return Node{leftNode.leftValue, leftNode.leftFreq, leftNode.maxFreq, leftNode.leftValue, leftNode.leftFreq};
    }

    int leftValue = leftNode.leftValue;
    int leftFreq = leftNode.leftFreq;

    int rightValue = rightNode.rightValue;
    int rightFreq = rightNode.rightFreq;

    int maxFreq = max(leftNode.maxFreq, rightNode.maxFreq);

    if (leftNode.rightValue == rightNode.leftValue) {
        // Middle value.
        int middleValue = leftNode.rightValue;
        int middleFreq = leftNode.rightFreq + rightNode.leftFreq;

        maxFreq = max(maxFreq, middleFreq);
        // See if this overlaps the left and right value.
        if (middleValue == leftValue) {
            leftFreq = middleFreq;
        }
        if (middleValue == rightValue) {
            rightFreq = middleFreq;
        }
    }

    Node result{leftValue, leftFreq, maxFreq, rightValue, rightFreq};
    /* cerr << "Query (" << leftNode << ", " << rightNode << ") = " << result << endl; */
    return result;
}


class SegmentTree {
    vector<Node> tree;

public:
    SegmentTree(const vector<int> &A) {
        tree.resize(A.size() * 4);
        build(1, 0, A.size() - 1, A);
    }

    void build(size_t nodeIndex, size_t segLeft, size_t segRight, const vector<int> &A) {
        if (segLeft == segRight) {
            // Leaf node.
            int x = A[segLeft];
            tree[nodeIndex] = Node{x, 1, 1, x, 1};
        } else {
            size_t mid = segLeft + ((segRight - segLeft) / 2);
            size_t leftChild = 2 * nodeIndex;
            size_t rightChild = leftChild + 1;
            build(leftChild, segLeft, mid, A);
            build(rightChild, mid+1, segRight, A);
            tree[nodeIndex] = tree[leftChild] + tree[rightChild];
        }
    }

    Node query(size_t nodeIndex, size_t segLeft, size_t segRight, size_t qryLeft, size_t qryRight) {
        // Disjoint
        if (segRight < qryLeft || qryRight < segLeft) {
            return Node{0, 0, 0, 0, 0};
        }
        // Entirely covered.
        if (qryLeft <= segLeft && segRight <= qryRight) {
            return tree[nodeIndex];
        }
        // Don't know.
        size_t mid = segLeft + ((segRight - segLeft) / 2);
        size_t leftChild = 2 * nodeIndex;
        size_t rightChild = leftChild + 1;
        return query(leftChild, segLeft, mid, qryLeft, qryRight) + query(rightChild, mid+1, segRight, qryLeft, qryRight);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    size_t N{0}, Q{0};
    cin >> N;
    while (N) {
        cin >> Q;
        vector<int> A;
        A.reserve(N);
        copy_n(istream_iterator<int>(cin), N, back_inserter(A));
        SegmentTree st(A);
        /* cerr << "Segment tree constructed ..." << endl; */
        for (size_t q{0}; q < Q; ++q) {
            size_t qryLeft{0}, qryRight{0};
            cin >> qryLeft >> qryRight;
            qryLeft--; qryRight--;  // convert to 0-based.
            /* cerr << "Query " << qryLeft << ", " << qryRight << endl; */
            Node answer = st.query(1, 0, A.size()-1, qryLeft, qryRight);
            /* cerr << "answer " << answer << endl; */
            cout << answer.maxFreq << endl;
        }
        cin >> N;
    }
    return EXIT_SUCCESS;
}
