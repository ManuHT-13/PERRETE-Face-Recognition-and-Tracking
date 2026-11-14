import argparse
from ultralytics import YOLO

parser = argparse.ArgumentParser()
parser.add_argument("--model", type=str, required=True)
parser.add_argument("--imgsz", type=int, default=640)
parser.add_argument("--batch", type=int, default=1)
parser.add_argument("--opset", type=int, default=17)
parser.add_argument("--half", action="store_true")
parser.add_argument("--int8", action="store_true")
parser.add_argument("--no-simplify", action="store_true")
parser.add_argument("--dynamic", action="store_true")

args = parser.parse_args()

model = YOLO(args.model)

model.export(
    format="onnx",
    imgsz=args.imgsz,
    batch=args.batch,
    half=args.half,
    int8=args.int8,
    dynamic=args.dynamic,
    simplify=not args.no_simplify,
    device=0,
    opset=args.opset
)