import {createRouter, createWebHashHistory} from "vue-router";

import LoginPage from "@/components/LoginPage";
import FrontPage from "@/components/FrontPage";
import MainPage from "@/components/MainPage";
import SensorMangePage from "@/components/SensorMangePage";
import DroneManagePage from "@/components/DroneManagePage";
import SettingPage from "@/components/SettingPage";

const routes = [
    {
        path: '/',
        redirect: '/home',
    },
    {
        path: '/login',
        component: LoginPage,
    },
    {
        path: '/home',
        redirect: '/home/drone',
        component: MainPage,
        children: [
            {
                path: 'front',
                component: FrontPage,
            },
            {
                path: 'sensor',
                component: SensorMangePage,
            },
            {
                path: 'drone',
                component: DroneManagePage,
            },
            {
                path: 'setting',
                component: SettingPage,
            },
        ]
    },
]

const router = createRouter({
    history: createWebHashHistory(),
    routes,
})

export default router;