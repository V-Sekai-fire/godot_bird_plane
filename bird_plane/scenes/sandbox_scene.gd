extends Node3D

@export var smooth_follow: Sandbox_BirdPlaneCoreSmoothFollowSmoothFollow
@export var thrust: Sandbox_BirdPlaneCoreThrustThrust
@export var turning: Sandbox_BirdPlaneCoreTurningTurning

var sensitivity: float
var mouse_speed: Vector2

func _process(delta: float):
	var plane: Node3D = get_node("Plane")
	var camera: Node3D = get_node("Camera")
	smooth_follow._process_parent_child(delta, plane, camera)
	thrust._physics_process_plane(delta, plane)


func _physics_process(_delta) -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED
	#$Turning._physics_process_plane(delta, plane)
	
func _input(event: InputEvent):
	var plane: Node3D = get_node("Plane")

	if event is InputEventMouseMotion:
		mouse_speed = mouse_speed.lerp(event.get_relative() / 1000, sensitivity);
		turning._input_plane(event, plane, mouse_speed)
