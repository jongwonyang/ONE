> [!TIP]
> 우측 상단의 버튼으로 **목차**를 확인할 수 있습니다.

# ✨ ONE (On-device Neural Engine)

| 항목          | 내용 |
|--------------|------|
| 🕒 기간      | 2024-09 ~ 2024-10 |
| 👥 인원      | 6명 |
| 🛠 사용 기술 | <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++"/> <img src="https://img.shields.io/badge/TensorFlow-%23FF6F00.svg?style=for-the-badge&logo=TensorFlow&logoColor=white" alt="TensorFlow"/> <img src="https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white" alt="GitHub"/> <img src="https://img.shields.io/badge/Samsung-%231428A0.svg?style=for-the-badge&logo=samsung&logoColor=white" alt="Samsung"/> |
| 🎯 담당 역할 | 1) LLM 지원을 위한 reshape 연산의 dynamic input shape 호환성 개선<br/>2) Logistic 연산 리팩토링 |
| 📖 개요      | 삼성전자 제품에 사용되는 온-디바이스 뉴럴 엔진 프레임워크 (오픈소스 기여) |

# 💡 프로젝트 개요
## 배경 및 목표
- ONE이란?
  - 삼성전자의 오픈소스, 온디바이스 AI 풀스택 프레임워크입니다.
  - ONE을 통해 다양한 AI 모델을 스마트폰, TV, 냉장고와 같은 엣지 디바이스 환경에서 사용할 수 있습니다.
- Shape Inference란?
  - 각 연산에서 입력 데이터를 이용하여 출력 데이터의 모양을 **실행 전에** 추론해주는 것입니다.
  - 이를 통해 memory allocation planning 등의 기능을 지원하여 런타임 성능을 향상시킬 수 있습니다.
- Dynamic Input Shape이란?
  - 최근 ONE은 LLM을 지원하는것을 목표로 하고 있습니다.
  - LLM은 이전 입력과 출력이 다음 입력에 재사용된다는 특성이 있습니다.
  - 이러한 특성 때문에 LLM은 실행 전에 입력의 모양을 미리 결정해 놓을 수 없습니다.
  - 이를 Dynamic Input Shape이라고 합니다.
  - 기존 ONE은 Dynamic Input Shape에 대해 0이라는 잘못된 값으로 추론하는 문제가 있었습니다.
- 본 프로젝트에서는 [Dynamic Shape에 대해 Shape Inference를 지원하도록 개선하는 이슈](https://github.com/Samsung/ONE/issues/13697)를 해결하는것을 목표로 합니다.

## 주요 기여
### ✅ 동적 모양 추론
다음 연산들이 Dynamic Shape에 대해 Shape Inference를 지원하도록 수정했습니다.

- First milestone (for token gen model)

Op | assignee
-- | --
concat | @jinevening 
transpose | Already supported
batchmatmul | @zetwhite 
div | @jinevening 
add | @jinevening 
softmax | @jinevening 

- Second milestone (for the whole (prompt parsing, token gen) model)

Op | assignee
-- | --
mul | @qsunki 
fully_connected| @Hanjin-Choi 
rsqrt | @pcs1265 
quantize | @kyeong8139 
reshape | @jongwonyang 
stridedslice | @qsunki 
neg | @Hanjin-Choi 
logistic | @jongwonyang 

- Others (for any other issues)

Op | assignee
-- | --
pad | @icodo98 
range | @kyeong8139 
conv2d | @pcs1265 

### ✅ 통합 테스트
위에서 수정한 Shape Inference가 ONE에서 잘 동작하는지 확인하기 위해 자동화 테스트를 구축하였습니다.

테스트는 다음과 같이 동작합니다.

1. `.recipe` 파일에 테스트를 위한 모델을 정의합니다.
2. `.rule` 파일에 테스트하고 싶은 요소를 `RULE <name> <검사 항목> <예상 결과>` 형태로 작성합니다.

![image](https://github.com/user-attachments/assets/b27f7a56-87bf-443b-b1e0-59ab53f9d353)

3. `.recipe` 파일은 TensorFlow 모델 형식인 `.tflite` 파일로 변환됩니다.
4. 이후 ONE 모델 형식인 `.circle` 파일로 변환됩니다.

![image](https://github.com/user-attachments/assets/f42ea9fe-ef37-473b-80d1-3ca64c4ca625)

5. 마지막으로 `.rule`에 작성된 기대값과 `.circle` 파일에 의해 변환된 데이터의 shape이 일치하는지 비교합니다.

![image](https://github.com/user-attachments/assets/785a66c6-c36d-4345-a3e1-f5b78a4c3071)

위 테스트를 통해 본 프로젝트에서 지원한 Dynamic Shape Inference가 ONE의 통합된 환경에서도 의도한대로 정상 동작함을 확인할 수 있습니다.

# 🔥 나의 기여
## 1️⃣
