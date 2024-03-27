## UnrealSlash

A Unreal Engine 5 MMORPG Game

## 🛠️ Tooling

#### Tilesets


```bash
여기에 내용 추가해보기
```

## ✅ Todo list

#### Now Doing
- [ ] 코드 다시보면서 분석하기

#### Something To Memo
- Inverse Kinematics (경사진 곳에서 다리 내리거나 하는 효과)
- IK Rig로 Animation 따기 (XBot from mixamo -> Echo), IK Retargeting
- Weapon Socket 만들어서 애니메이션 실행해도 무기의 위치가 적절한지 보고 수정하기
- Linked anim graph로 애니메이션 블루프린트 연결하기
- Anim Montage로 공격, Item Equip, Hit React을 만들기
- MetaSounds로 다른 오디오 파일 튼 거 같은 효과 내기
- Niagara Particle Effects 사용하기
- Key를 사용해서 Additive Layer Track에서 애니메이션 조금 수정했다가 변경사항 다시 원래 애니메이션에 맞게 돌아가게 해서
- Notify를 이용해 무기의 Collsion 껐다 켜서 필요할때만 Overlap하도록 하고, Channel를 조절하여 원하는 대상만 공격
- Interface를 통해 상속한 대상만 공격하도록 하기
- Blender의 Mixamo converter addon을 이용해서 Root Bone이 없는 Mixamo Character에 Root Bone 추가해줘서 Root animation 적용하기
- Dot Product, Cross Product를 이용해서 무기가 적을 어느 각도에서 때리는지 파악
- Sound Attenuation을 이용해서 거리에 따라 들리는 Sound 다르게 하기
- Cascade Particle System(Legacy)와 Niagara Particle System을 이용해서 파티클 이펙트 추가하기(피)
- 무기 Tracing Cascade Particle System을 이용해서 무기 효과 적용
- Mesh를 Destructible Mesh로 만들고 Field System을 이용해서 무기로 공격했을 때 잘게잘게 부서지는 효과 적용
- virtual 함수 Blueprint에서도 override하기 위해 UFUNCTION(BlueprintNativeEvent)를 선언하면 Blueprint에서도 가져올 수 있고, C++에서는 GetHit_Implementation이라고 명명을 바꾸면 됨
- Destructible Mesh 부서지는 음성 추가(MetaSounds) + Sound Attenuation
-  
#### Items

- ✅ 아이템 만들기