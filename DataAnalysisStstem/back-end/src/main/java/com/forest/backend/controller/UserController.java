package com.forest.backend.controller;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.forest.backend.Data.User;
import com.forest.backend.mapper.UserMapper;
import com.forest.backend.utils.JsonResult;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
@RequestMapping("/user")
public class UserController {

    @Resource
    UserMapper userMapper;

    @PostMapping("/login")
    public JsonResult<User> userLogin(@RequestParam String username, @RequestParam String password) {
        QueryWrapper<User> wrapper = new QueryWrapper<>();
        wrapper.select("id", "name").eq("name", username).eq("password", password);
        User user = userMapper.selectOne(wrapper);

        if (user != null) {
            return new JsonResult<>(user);
        }

        return new JsonResult<>();
    }
}
