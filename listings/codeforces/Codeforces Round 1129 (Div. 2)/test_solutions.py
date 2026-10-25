"""Independent local checks. Usage: python test_solutions.py --bin-dir ../work
Build A.cpp ... F.cpp as A.exe ... F.exe (or extensionless executables) first.
Only the Python standard library is needed. Fixed seed makes runs reproducible.
"""
import argparse
import collections
import functools
import itertools
from pathlib import Path
import random
import subprocess
import time

MOD = 998244353
RNG = random.Random(2277)
parser = argparse.ArgumentParser()
parser.add_argument('--bin-dir', type=Path, default=Path(__file__).resolve().parent)
parser.add_argument('--stress', action='store_true')
args = parser.parse_args()


def executable(name):
    for suffix in ('.exe', ''):
        path = args.bin_dir.resolve() / (name + suffix)
        if path.is_file():
            return str(path)
    raise FileNotFoundError(f'Build {name}.cpp into {args.bin_dir} first')


def run(name, cases, expected):
    data = str(len(cases)) + '\n' + '\n'.join(cases) + '\n'
    result = subprocess.run([executable(name)], input=data, text=True,
                            capture_output=True, timeout=90, check=True)
    actual = list(map(int, result.stdout.split()))
    assert actual == expected, (name, next(((i, a, b) for i, (a, b) in
        enumerate(itertools.zip_longest(actual, expected)) if a != b), None))
    print(f'{name}: {len(cases)} cases passed', flush=True)


def tree(n):
    edges = [(RNG.randrange(1, v), v) for v in range(2, n + 1)]
    labels = list(range(1, n + 1))
    RNG.shuffle(labels)
    return [(labels[u - 1], labels[v - 1]) for u, v in edges]


def graph(n, edges):
    g = [[] for _ in range(n + 1)]
    for u, v in edges:
        g[u].append(v)
        g[v].append(u)
    return g


def edge_text(edges):
    return '\n'.join(f'{u} {v}' for u, v in edges)


def check_a():
    cases, answers = [], []
    for _ in range(1300):
        n = RNG.randrange(1, 9)
        k = RNG.randrange(1, n + 1)
        a = [RNG.randrange(n + 1) for _ in range(n)]
        groups = [(sum(1 << i for i in subset), max(a[i] for i in subset))
                  for subset in itertools.combinations(range(n), k)]

        @functools.lru_cache(None)
        def brute(used, target):
            best = target
            for mask, value in groups:
                if value == target and not (used & mask):
                    best = max(best, brute(used | mask, target + 1))
            return best

        cases.append(f'{n} {k}\n' + ' '.join(map(str, a)))
        answers.append(brute(0, 0))
    run('A', cases, answers)


@functools.lru_cache(None)
def good(a):
    if a and all(x == 0 for x in a):
        return True
    for left in range(len(a)):
        for right in range(left, len(a)):
            if a[right] == 0:
                break
            for removed in range(left, right + 1):
                nxt = tuple(x - (left <= i <= right) for i, x in enumerate(a)
                            if i != removed)
                if good(nxt):
                    return True
    return False


def check_b():
    cases, answers = [], []
    arrays = [a for n in range(1, 6) for a in itertools.product(range(5), repeat=n)]
    arrays += [tuple(RNG.randrange(10) for _ in range(RNG.randrange(1, 8)))
               for _ in range(600)]
    for a in arrays:
        best = 0
        for mask in range(1, 1 << len(a)):
            if mask.bit_count() > best:
                subseq = tuple(x for i, x in enumerate(a) if mask >> i & 1)
                if good(subseq):
                    best = len(subseq)
        cases.append(f'{len(a)}\n' + ' '.join(map(str, a)))
        answers.append(best)
    run('B', cases, answers)


def path(n, edges, source, target):
    g = graph(n, edges)
    parent = {source: 0}
    queue = [source]
    for u in queue:
        for v in g[u]:
            if v not in parent:
                parent[v] = u
                queue.append(v)
    route = []
    while target != source:
        route.append(tuple(sorted((target, parent[target]))))
        target = parent[target]
    return route


def check_c():
    cases, answers = [], []
    for _ in range(650):
        n = RNG.randrange(2, 8)
        edges = tree(n)
        operations = [RNG.randrange(2, n + 1) for _ in range(RNG.randrange(1, 6))]
        states = {tuple(sorted(tuple(sorted(e)) for e in edges))}
        for v in operations:
            next_states = set(states)  # Delete the new edge.
            new = (1, v)
            for state in states:
                for removed in path(n, state, 1, v):
                    changed = list(state)
                    changed.remove(removed)
                    changed.append(new)
                    next_states.add(tuple(sorted(changed)))
            states = next_states
        answers.append(max(len(path(n, state, 1, n)) for state in states))
        cases.append(f'{n} {len(operations)}\n{edge_text(edges)}\n'
                     + ' '.join(map(str, operations)))
    run('C', cases, answers)


def check_d():
    # BFS uses the original operations, with no recurrence from the solution.
    limit = 8191
    queue = collections.deque([(0, 0)])
    distance = {(0, 0): 0}
    best = [None] * (limit + 1)
    while queue:
        x, streak = queue.popleft()
        d = distance[x, streak]
        if best[x] is None:
            best[x] = d
        for nx, ns in ((x - 1, 0), (x + (1 << streak), streak + 1)):
            if 0 <= nx <= limit and (nx, ns) not in distance:
                distance[nx, ns] = d + 1
                queue.append((nx, ns))
    cases = [f'{n} {n}' for n in range(4096)]
    answers = best[:4096]
    for _ in range(250):
        l = RNG.randrange(4096)
        r = RNG.randrange(l, 4096)
        cases.append(f'{l} {r}')
        answers.append(sum(best[l:r + 1]) % MOD)
    # Keep D1 batches within the statement's sum-of-lengths constraint.
    for start in range(0, len(cases), 100):
        run('D1', cases[start:start + 100], answers[start:start + 100])
    run('D2', cases, answers)
    sample = ['4 4', '1 3', '127 127', '0 1000',
              '999999999999900001 1000000000000000000']
    expected = [6, 6, 7, 25383, 102936941]
    run('D1', sample, expected)
    run('D2', sample, expected)
    narrow = []
    for k in range(2, 60):
        center = 1 << k
        narrow.append(f'{max(0, center - 10)} {center + 10}')
    for _ in range(180):
        l = RNG.randrange(10**18 - 80)
        narrow.append(f'{l} {l + RNG.randrange(80)}')
    data = str(len(narrow)) + '\n' + '\n'.join(narrow) + '\n'
    expected = list(map(int, subprocess.run([executable('D1')], input=data,
        text=True, capture_output=True, check=True, timeout=60).stdout.split()))
    run('D2', narrow, expected)


def check_e():
    trees = [(n, tree(n)) for n in [RNG.randrange(2, 35) for _ in range(100)]]
    for n in (2, 3, 50, 500):
        trees.append((n, [(i, i + 1) for i in range(1, n)]))
        trees.append((n, [(1, i) for i in range(2, n + 1)]))
    trees.append((500, tree(500)))
    # Each batch respects the official sum(n) <= 500 constraint.
    batches = [[]]
    for item in trees:
        if sum(n for n, _ in batches[-1]) + item[0] > 500:
            batches.append([])
        batches[-1].append(item)
    for batch in batches:
        proc = subprocess.Popen([executable('E')], stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                text=True, bufsize=1)

        def send(value):
            proc.stdin.write(str(value) + '\n')
            proc.stdin.flush()

        try:
            send(len(batch))
            for n, edges in batch:
                send(n)
                g = graph(n, edges)
                queries = 0
                while True:
                    line = proc.stdout.readline().split()
                    assert line, 'Interactor: unexpected EOF'
                    if line[0] == '!':
                        recovered = set()
                        for _ in range(n - 1):
                            u, v = map(int, proc.stdout.readline().split())
                            recovered.add(tuple(sorted((u, v))))
                        assert recovered == {tuple(sorted(e)) for e in edges}
                        assert queries <= 2 * n - 2
                        break
                    assert line[0] == '?' and len(line) == n + 2
                    queries += 1
                    assert queries <= 2 * n - 2
                    x = int(line[1])
                    p = [0] + list(map(int, line[2:]))
                    assert 1 <= x <= n and sorted(p[1:]) == list(range(1, n + 1))
                    stack = [(x, 0, p[x])]
                    reply = 0
                    for u, parent, maximum in stack:
                        reply += maximum
                        for v in g[u]:
                            if v != parent:
                                stack.append((v, u, max(maximum, p[v])))
                    send(reply)
            proc.stdin.close()
            assert proc.wait(timeout=10) == 0
        finally:
            if proc.poll() is None:
                proc.kill()
    # The protocol requires immediate exit after -1.
    result = subprocess.run([executable('E')], input='1\n2\n-1\n', text=True,
                            capture_output=True, timeout=10, check=True)
    assert len(result.stdout.splitlines()) == 1
    print(f'E: {len(trees)} hidden trees and -1 termination passed', flush=True)


def brute_f(n, edges, a, permutation):
    g = graph(n, edges)
    result = []
    for root in range(1, n + 1):
        parent = [0] * (n + 1)
        order = [root]
        for u in order:
            for v in g[u]:
                if v != parent[u]:
                    parent[v] = u
                    order.append(v)
        descendants = [{u} for u in range(n + 1)]
        for u in reversed(order[1:]):
            descendants[parent[u]].update(descendants[u])
        tokens = [0] + a[:]
        cost = 0
        for u in permutation:
            amount = sum(tokens[v] for v in descendants[u])
            cost += amount
            for v in descendants[u]:
                tokens[v] = 0
            tokens[u] = amount
        result.append(cost % MOD)
    return result


def check_f():
    cases, answers = [], []
    for _ in range(3200):
        n = RNG.randrange(1, 11)
        edges = tree(n)
        a = [RNG.choice([0, RNG.randrange(30), MOD - 1]) for _ in range(n)]
        permutation = list(range(1, n + 1))
        RNG.shuffle(permutation)
        cases.append(f'{n}\n{edge_text(edges)}\n' + ' '.join(map(str, a))
                     + '\n' + ' '.join(map(str, permutation)))
        answers.extend(brute_f(n, edges, a, permutation))
    run('F', cases, answers)


def stress():
    n = 500000
    chain = '\n'.join(f'{i} {i + 1}' for i in range(1, n))
    start = time.perf_counter()
    run('C', [f'{n} {n}\n{chain}\n' + ' '.join(map(str, range(2, n + 1)))
              + ' 2'], [n - 1])
    print(f'C maximum path: {time.perf_counter() - start:.3f}s', flush=True)
    start = time.perf_counter()
    # All tokens start at 1; operations run 1,2,...,n. For root r,
    # vertices 1..r-1 cost 1,2,...,r-1; r costs n; later costs zero.
    a = ' '.join(['1'] * n)
    p = ' '.join(map(str, range(1, n + 1)))
    expected = [(n + r * (r - 1) // 2) % MOD for r in range(1, n + 1)]
    run('F', [f'{n}\n{chain}\n{a}\n{p}'], expected)
    print(f'F maximum path: {time.perf_counter() - start:.3f}s', flush=True)
    start = time.perf_counter()
    cases = ['0 1000000000000000000'] * 10000
    data = str(len(cases)) + '\n' + '\n'.join(cases) + '\n'
    result = subprocess.run([executable('D2')], input=data, text=True,
        capture_output=True, check=True, timeout=30).stdout.split()
    assert len(result) == 10000 and len(set(result)) == 1
    print(f'D2 10000 maximum-width queries: {time.perf_counter() - start:.3f}s', flush=True)


if __name__ == '__main__':
    start = time.perf_counter()
    for check in (check_a, check_b, check_c, check_d, check_e, check_f):
        check()
    if args.stress:
        stress()
    print(f'All checks passed in {time.perf_counter() - start:.2f}s')
