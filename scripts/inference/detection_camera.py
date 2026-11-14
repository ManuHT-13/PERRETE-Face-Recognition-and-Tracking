import cv2
import argparse
from ultralytics import YOLO


parser = argparse.ArgumentParser()
parser.add_argument("--camera", type=int, default=0)
parser.add_argument("--model", type=str, required=True)

args = parser.parse_args()

cap = cv2.VideoCapture(args.camera)
model = YOLO(args.model)

while True:
    ret, frame = cap.read()

    if not ret:
        break

    results = model.track(frame, persist=True)
    annotated_frame = results[0].plot()
    cv2.imshow("Camera Detection", annotated_frame)

    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()