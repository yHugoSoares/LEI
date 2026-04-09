from dataclasses import dataclass
from hypothesis import given, strategies as st
import string
from typing import List, Tuple


@dataclass
class MyString:
    data: List[Tuple[str, int]]
    
    def __eq__(self, other):
        if not isinstance(other, MyString):
            return NotImplemented
        
        if len(self.data) != len(other.data):
            return False
        
        # Converts the list of tuples into a dictionary
        self_map = {pos: char for char, pos in self.data}
        other_map = {pos: char for char, pos in other.data}
        
        return self_map == other_map


braga = MyString([('a', 3), ('g', 4), ('r', 2), ('B', 1), ('a', 5)])


def from_string(s: str) -> MyString:
    return MyString(list(zip(s, range(1, len(s) + 1))))


def to_string(my_str: MyString) -> str:
    return ''.join(char for char, pos in sorted(my_str.data, key=lambda x: x[1]))

@st.composite
def gen_my_string(draw):
    s = draw(st.text(alphabet=string.ascii_letters, min_size=1))
    return from_string(s)



@given(st.text())
def test_from_to(s):
    assert to_string(from_string(s)) == s


@given(gen_my_string())
def test_to_from(my_str):
    assert from_string(to_string(my_str)) == my_str


