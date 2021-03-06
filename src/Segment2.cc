#include "Segment2.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace v8;
using namespace node;
using namespace std;


const char *Segment2::Name = "Segment2";


void Segment2::RegisterMethods()
{
    SetPrototypeMethod(sConstructorTemplate, "isVertical", IsVertical);
    SetPrototypeMethod(sConstructorTemplate, "isHorizontal", IsHorizontal);
}


bool Segment2::ParseArg(Local<Value> arg, Segment_2 &receiver)
{
    if (sConstructorTemplate->HasInstance(arg)) {
        receiver = ExtractWrapped(Local<Object>::Cast(arg));
        return true;
    }

    if (arg->IsObject()) {
        Local<Object> ends = Local<Object>::Cast(arg);

        Point_2 source, target;

        if (Point2::ParseArg(ends->Get(String::NewSymbol("source")), source) &&
            Point2::ParseArg(ends->Get(String::NewSymbol("target")), target))
        {
            receiver = Segment_2(source, target);
            return true;
        }

    }

    return false;
}


Handle<Value> Segment2::ToPOD(const Segment_2 &segment, bool precise)
{
    HandleScope scope;
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("source"), Point2::ToPOD(segment.source(), precise));
    obj->Set(String::NewSymbol("target"), Point2::ToPOD(segment.target(), precise));
    return scope.Close(obj);
}


Handle<Value> Segment2::IsHorizontal(const Arguments &args)
{
    HandleScope scope;
    try {
        Segment_2 &segment = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(segment.is_horizontal()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}


Handle<Value> Segment2::IsVertical(const Arguments &args)
{
    HandleScope scope;
    try {
        Segment_2 &segment = ExtractWrapped(args.This());
        return scope.Close(Boolean::New(segment.is_vertical()));
    }
    catch (const exception &e) {
        return ThrowException(String::New(e.what()));
    }
}
