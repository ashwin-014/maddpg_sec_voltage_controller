import logging
from gym.envs.registration import register

logger = logging.getLogger(__name__)

register(
    id='Multiagent-final-eval-v0',
    entry_point='custom_env_final_eval.custom_env_test_final_eval:MultiAgent',
)