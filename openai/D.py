import ast
from typing import List

class ImportsHelper(ast.NodeVisitor):
    def __init__(self):
        self.out = []

    def visit_Import(self, node):
        for imp in node.names:
            self.out.append(imp.name)

    def visit_ImportFrom(self, node):
        for imp in node.names:
            self.out.append(f"{node.module}.{imp.name}")

def parse_imports(code: str) -> List[str]:
    pc = ast.parse(code)
    ih = ImportsHelper()
    ih.visit(pc)
    result = ih.out
    result.sort()
    return result


# Examples
# print(parse_imports('import os'))
print(parse_imports('import os\nfrom typing import List'))
