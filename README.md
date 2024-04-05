## UnrealSlash

A Unreal Engine 5 MMORPG Game

## 🛠️ Tooling

#### Tilesets


```bash
여기에 내용 추가해보기
```

## ✅ Todo list
- [ ] 양손무기로 똑같은 거 만들기, 애니메이션도
- [ ] 한손무기에서 두손무기로 바꾸거나 하기
- [ ] Destructs 종류 늘리고 부수면 나오는 것들 종류 다르게 하기
- [ ] Destructible 부술때 파편에 옆에 있는거 부셔지는거 방지하기
- 

#### Now Doing
- [ ] 코드 다시보면서 분석하기

#### Something To Memo
- ✅ Inverse Kinematics (경사진 곳에서 다리 내리거나 하는 효과)
- ✅ IK Rig로 Animation 따기 (XBot from mixamo -> Echo), IK Retargeting
- ✅ Weapon Socket 만들어서 애니메이션 실행해도 무기의 위치가 적절한지 보고 수정하기
- ✅ Linked anim graph로 애니메이션 블루프린트 연결하기
- ✅ Anim Montage로 공격, Item Equip, Hit React을 만들기
- ✅ MetaSounds로 다른 오디오 파일 튼 거 같은 효과 내기
- ✅ Niagara Particle Effects 사용하기
- ✅ Key를 사용해서 Additive Layer Track에서 애니메이션 조금 수정했다가 변경사항 다시 원래 애니메이션에 맞게 돌아가게 해서
- ✅ Notify를 이용해 무기의 Collsion 껐다 켜서 필요할때만 Overlap하도록 하고, Channel를 조절하여 원하는 대상만 공격
- ✅ Interface를 통해 상속한 대상만 공격하도록 하기
- ✅ Blender의 Mixamo converter addon을 이용해서 Root Bone이 없는 Mixamo Character에 Root Bone 추가해줘서 Root animation 적용하기
- ✅ Dot Product, Cross Product를 이용해서 무기가 적을 어느 각도에서 때리는지 파악
- ✅ Sound Attenuation을 이용해서 거리에 따라 들리는 Sound 다르게 하기
- ✅ Cascade Particle System(Legacy)와 Niagara Particl~~~~e System을 이용해서 파티클 이펙트 추가하기(피)
- ✅ 무기 Tracing Cascade Particle System을 이용해서 무기 효과 적용
- ✅ Mesh를 Destructible Mesh로 만들고 Field System을 이용해서 무기로 공격했을 때 잘게잘게 부서지는 효과 적용
- ✅ virtual 함수 Blueprint에서도 override하기 위해 UFUNCTION(BlueprintNativeEvent)를 선언하면 Blueprint에서도 가져올 수 있고, C++에서는 GetHit_Implementation이라고 명명을 바꾸면 됨
- ✅ Destructible Mesh 부서지는 음성 추가(MetaSounds) + Sound Attenuation
- ✅ Niagara System, Niagara Emitter을 이용해서 아이템 주울 수 있는 상태인 걸 알리는 Particle를 만들고 Niagra를 C++,에서 이용함
- ✅ HealthBarComponent라는 ActorComponent를 하나 ~~~~만들어서 HP를 보여야 하는 액터에 추가한 후 WBP_HealthBar이 HealthBar(UserWidget)을 상속하게 만들어서 온갖 변수들 변화하게 함으로써 체력표시
- ✅ BlueprintThreadSafeUpdate을 override해서 다양한 애니메이션마다 Tick을 두어서 서로한테 영향을 주거나 느려짐을 방지
- ✅ ProjectSetting에서 NavigationMesh의 RuntimeGeneration을 Dynamic으로 두어서 Navmesh를 계속 변하게 함
- ✅ Import한 무기가 Root이 다르면 그걸 blender로 import해서 조정한다음에 export해서 사용, 이렇게 모든 무기 손잡이로 가능
- ✅ 애니메이션 추가할때 이상한 부분 있으면 앞뒤로 Key 설정하고 중간에 바꾼부분을 key로 만들어서 자연스럽게 바꿈
#### Items

- ✅ 아이템 만들기