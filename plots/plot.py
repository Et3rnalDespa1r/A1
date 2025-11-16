import math
import pandas as pd
import matplotlib.pyplot as plt

S_exact = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1.0

df = pd.read_csv("../results.csv")


if "абсолютная_ошибка" not in df.columns or "относительная_ошибка" not in df.columns:
    df["абсолютная_ошибка"] = (df["площадь"] - S_exact).abs()
    df["относительная_ошибка"] = df["абсолютная_ошибка"] / S_exact

plt.figure()
for rect_type in ["широкий", "узкий"]:
    sub = df[df["тип_прямоугольника"] == rect_type]
    plt.plot(sub["N"], sub["площадь"], label=rect_type)

plt.axhline(S_exact, linestyle="--")

plt.xlabel("N")
plt.ylabel("Оценка площади")
plt.title("Зависимость оценки площади от N")
plt.legend()
plt.tight_layout()
plt.savefig("area_vs_N.png", dpi=200)
plt.close()

plt.figure()
for rect_type in ["широкий", "узкий"]:
    sub = df[df["тип_прямоугольника"] == rect_type]
    plt.plot(sub["N"], sub["относительная_ошибка"], label=rect_type)

plt.xlabel("N")
plt.ylabel("Относительная ошибка")
plt.title("Зависимость относительной ошибки от N")
plt.legend()
plt.tight_layout()
plt.savefig("error_vs_N.png", dpi=200)
plt.close()
