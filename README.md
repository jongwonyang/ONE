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
  - 기존 ONE은 Dynamic Input Shape에 대해 optimize시 잘못된 값으로 추론하는 문제가 있었습니다.
- 본 프로젝트에서는 [Dynamic Shape에 대해 Shape Inference를 지원하도록 개선하는 이슈](https://github.com/Samsung/ONE/issues/13697)를 해결하는것을 목표로 합니다.

## 주요 기여 (팀)
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
## 1️⃣ Reshape 연산의 Dynamic Shape Inference 지원
### 상황
- 기존 reshape 연산은 optimize 단계에서 dynamic input shape에 대해 output shape을 잘못 추론하는 문제가 있었습니다.
- Dynamic shape을 어떻게 올바르게 처리할지 1) 정책을 세우고 2) 해당 정책을 구현하는 것이 목표입니다.

### TensorFlow의 동작 분석
- 기존 ONE에서는 dynamic shape에 대한 고려가 없었기 때문에 이를 처리할 규칙은 TesorFlow의 것을 따르기로 하였습니다.
- 기존 모델들에 대해 TensorFlow에서는 input과 output의 모양에 따라 어떻게 추론을 수행하는지 분석했습니다. 그 결과는 다음과 같습니다.

![tensorflow-behavior](https://github.com/user-attachments/assets/e4747417-e7f9-43d9-baf2-60786d62f4de)

- 2x2 matrix를 작성함으로써 발생할 수 있는 모든 상황에 대한 coverage를 갖는 정책을 세울 수 있었습니다.

### 정책 구현 중 문제점
위에서 도출한 TensorFlow의 정책에 따라 구현하던 중 다음과 같은 문제가 발생했습니다.

- `node->shape()`를 `CircleNode`로 캐스팅하면 `shape->rank()`가 항상 1을 반환하는 문제가 발생했습니다.
- 이는 기존의 잘못된 동작에 대한 원인이면서 `TensorShape` 믹스인이 노드 자체의 `shape` 정보만 포함하기 때문에 발생하는 문제였습니다.
- 예를 들어, 어떤 노드의 값에 `[2, 3, 4]`라는 새로운 `shape` 정보가 있더라도, 노드 자체의 `shape`는 `[3]`으로 저장되었습니다.
- 따라서 `rank()`는 1을 반환하고, `dim(0)`은 3을 반환하는 문제를 기존 설계에서는 쉽게 수정하기가 어려운 상황입니다.

따라서 현재 구조에서는 노드의 실제 값에 접근할 수 없으므로, 가능한 정보 내에서 가장 합리적인 방식으로 대응하고자 했습니다.

그렇게 구현한 결과는 다음과 같습니다.

```cpp
auto shape = loco::must_cast<luci::CircleNode *>(node->shape());
shape_by_input.rank(shape->dim(0).value());
for (uint32_t r = 0; r < shape_by_input.rank(); ++r)
{
  shape_by_input.dim(r).unset();
}
is_static_shape = false;
```

- `CircleNode`의 경우 `[?, ?, ?]`(rank 3)를 반환하도록 구현하여 일관된 방식으로 처리하도록 하였습니다.
- 이 방식은 현재 코드 구조를 유지하면서도 안정적으로 동작하며, 예상치 못한 오류를 방지하는 역할을 합니다.


### 결과
문제를 해결한 과정을 리뷰어가 이해하기 쉽도록 작은 부분으로 나누어 다음과 같은 일련의 PR을 제출하였습니다.

- https://github.com/Samsung/ONE/pull/14037
- https://github.com/Samsung/ONE/pull/14061
- https://github.com/Samsung/ONE/pull/14128
- https://github.com/Samsung/ONE/pull/14139
- https://github.com/Samsung/ONE/pull/14113
- https://github.com/Samsung/ONE/pull/14117

해당 PR들이 master 브랜치에 merge됨으로써 reshape 연산에 대한 dynamic shape 이슈가 해결되었습니다.

이와 동시에 ONE 커뮤니티에 다음과 같이  궁극적으로 기존 설계 변경의 필요성을 제안하였습니다.

- 장기적으로는 기존 코드의 설계를 개선하여, 노드가 텐서의 실제 값(예: [2, 3, 4])을 보다 명확하게 가질 수 있도록 하는 것이 이상적입니다.
- 이를 위해 새로운 믹스인을 도입하거나, 텐서의 값을 직접 접근할 수 있는 구조적인 변경이 필요할 수 있습니다.
- 하지만 현재로서는 `[?, ?, ?]` 방식이 가장 안정적이고 적절한 해결책이며, 이를 통해 코드가 충분히 잘 동작하도록 구현하였습니다.

## 2️⃣ Logistic 연산의 Namespace 변경
### 상황
- Logistic (Sigmoid) 연산은 모양이 변하는 연산이 아니기 때문에 동적으로 shape inference를 수행할 필요는 없습니다. (기존에도 올바르게 동작)
- 하지만 dynamic shape을 지원하는 연산 set을 위한 namespace가 존재하기 때문에 향후 유지보수성을 위해 namespace를 migration 하였습니다.

### 결과
다음 PR을 제출하였고 master 브랜치에 merge되었습니다.

- https://github.com/Samsung/ONE/pull/14006
