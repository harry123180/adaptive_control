sound.play("Playdate.mp3");
 
setBackdrop("sky.jpg");
 
var sky=createSprite("sky.jpg");
sky.x=600;
sky.y=2400;
 
var koding=createSprite("koding.png");
koding.x=600;
koding.y=100;
 
var bird=createSprite("bird.png");
bird.x=1500;
bird.y=200;
 
var eagle=createSprite("eagle.png")
eagle.x=-500;
eagle.y=200;
 
var plane = createSprite("plane.png");
plane.x = -300
plane.y=200;
 
var pointer = createSprite("pointer.png");
pointer.x = 1095;
pointer.y = 610;
var map = createSprite("map.png");
map.x = 1100;
map.y = 700;
map.scale = 2;
 
function movePointer() {​​​​
 
    if (pointer.y < 800) {​​​​
        //pointer.y = 600 + 200*(2400-sky.y)/3900;
        pointer.y += 0.07;
    }​​​​ else {​​​​
        pointer.hidden = true;
        map.hidden = true;
    }​​​​
}​​​​
 
//====================================================//
 

//叩叮上下左右移動
function moveKoding(){​​​​{​​​​
    koding.direction=90;
    if(key.right&&koding.x<1200){​​​​
        koding.x+=5;
        koding.direction=100;
    }​​​​
    if(key.left&&koding.x>0){​​​​
        koding.x-=5;
        koding.direction=80;
    }​​​​
    
}​​​​
   
     if(key.up&& koding.y>0){​​​​
         koding.y-=5;
     }​​​​
     if(key.down&& koding.y<900){​​​​
         koding.y+=5;
     }​​​​
}​​​​
//背景上移，相當於叩叮往下掉
function fallDown() {​​​​
    if(sky.y>-1500)
     sky.y-=1.5;
}​​​​
 
//小鳥移動
function moveBird() {​​​​
    if(bird.x>1200&& sky.y>-1000){​​​​
        bird.x=Math.random()*300-500;//-500~-200
        bird.y=Math.random()*500+200;//200~700
    }​​​​
    bird.x+=2;
}​​​​
//老鷹移動
function moveEagle() {​​​​
    if(eagle.x<0){​​​​
         eagle.x=Math.random()*300+1400;
         eagle.y=Math.random()*500+200;
    }​​​​
    eagle.x-=4;
}​​​​
 
//飛機移動
function movePlane() {​​​​
     plane.x -=6;
     plane.y -=2;
     if(plane.x<0&& sky.y>-1000){​​​​
         
         plane.x= Math.random()*300+1400;
         plane.y= Math.random()*500+300;
     }​​​​
}​​​​
 
//叩叮安全降落
function landing() {​​​​
  if(sky.y<=-1500){​​​​
      if(koding.y<700){​​​​
          koding.y+=1;
      }​​​​
      else{​​​​
          win();
      }​​​​
  }​​​​
}​​​​
 
//勝利
function win() {​​​​
    stop();
    var youwin=createSprite("youwin.png");
}​​​​
koding.on('touch',[bird,eagle,plane],gameover);
//遊戲結束：失敗
function gameover() {​​​​
    stop();
    sound.play("crash.mp3");
    var explode=createSprite("explode.png");
    explode.x=koding.x;
    explode.y=koding.y;
    var gameover=createSprite("gameover.png");
}​​​​
 
// 不停地執行...
forever(function() {​​​​
    moveKoding();
    fallDown();
    movePointer();
    moveBird();
    moveEagle();
    movePlane();
    landing();
}​​​​);