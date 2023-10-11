from datatypes.Arg import make_arg_simple
from datatypes.Operand import Operand

import AnnotationGeneration

cmd_name = "mv"


def test_mv_1():
    args = [make_arg_simple(["-t", "dest"])]
    operands = [Operand("tomove1.txt"),
                Operand("tomove2.txt")]

    meta = AnnotationGeneration.get_meta_from_cmd_invocation(cmd_name, args, operands)
    assert len(meta.get_input_list()) == 2
    assert len(meta.get_output_list()) == 1


def test_mv_2():
    args = [make_arg_simple(["-v"])]
    operands = [Operand("tomove1.txt"),
                Operand("tomove2.txt"),
                Operand("dest.txt")]

    meta = AnnotationGeneration.get_meta_from_cmd_invocation(cmd_name, args, operands)
    assert len(meta.get_input_list()) == 2
    assert len(meta.get_output_list()) == 1


def test_mv_3():
    args = [make_arg_simple(["-t", "dest1.txt"]),
            make_arg_simple(["-t", "dest2.txt"])]
    operands = [Operand("tomove1.txt"),
                Operand("tomove2.txt"),
                Operand("dest.txt")]

    try:
        _meta = AnnotationGeneration.get_meta_from_cmd_invocation(cmd_name, args, operands)
        assert False
    except Exception:
        assert True


test_mv_1()
test_mv_2()
test_mv_3()
