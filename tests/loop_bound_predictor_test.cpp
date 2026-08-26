#include "../C/syntax/LoopBoundPredictor.h"
#include <cassert>

using psy::C::LoopBoundConfidence;
using psy::C::LoopBoundPredictor;

int main() {
    auto p = LoopBoundPredictor::predict("i = 0;", "i < 10", "i++", 64);
    assert(p.iterations == 10 && p.confidence == LoopBoundConfidence::Exact);
    p = LoopBoundPredictor::predict("int i = 2;", "i <= 10", "i = i + 2", 64);
    assert(p.iterations == 5);
    p = LoopBoundPredictor::predict("i = 10;", "i > 0", "i--", 64);
    assert(p.iterations == 10);
    p = LoopBoundPredictor::predict("i = 10;", "i >= 2", "i -= 2", 64);
    assert(p.iterations == 5);
    p = LoopBoundPredictor::predict("i = 0;", "i < n", "i++", 64);
    assert(p.iterations == 3 && p.confidence == LoopBoundConfidence::Fallback);
    p = LoopBoundPredictor::predict("i = 0;", "i < 1000", "i++", 32);
    assert(p.iterations == 32 && p.confidence == LoopBoundConfidence::Conservative);
    p = LoopBoundPredictor::predict("i = 10;", "i < 2", "i++", 64);
    assert(p.iterations == 0);
}
